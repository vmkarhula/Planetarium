#include "Renderer.h"

#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

#include "DearIMGui/imgui.h"
#include "DearIMGui/imgui_impl_glfw.h"
#include "DearIMGui/imgui_impl_opengl3.h"

#define TINYOBJLOADER_IMPLEMENTATION
#include "tinyobjloader/tiny_obj_loader.h"


Renderer::Renderer() :
	m_Window(nullptr),
	m_ScreenWidth(1280),
	m_ScreenHeight(720),
	m_DataLoader(nullptr),
	m_Framebuffer(0),
	m_CameraPos(0.0f, 0.0f, 0.0f),
	m_CameraUp(0.0f, 1.0f, 0.0f),
	m_Fov(70.0f),
	m_Projection(),
	m_View(),
	m_ViewProj(),
	m_AspectRatio(16.0 / 9.0),
	m_BasicShader(nullptr),
	m_ScreenQuadShader(nullptr),
	m_DummyTexture(nullptr),
	m_ScreenQuadVAO(0),
	m_TagIndex(0),
	m_HDR_ScreenQuadTexture(0),
	m_HDR_Framebuffer(0),
	m_Tonemapper(nullptr),
	m_HDR(true),
	m_Imgui_ShowRenderOptions(true)
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_Window = glfwCreateWindow(m_ScreenWidth, m_ScreenHeight, "OpenGL Planetarium", nullptr, nullptr);

	if (!m_Window) {

		std::cerr << "Error creating GLFW Window! \n";
	}

	glfwMakeContextCurrent(m_Window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);
	
	glClearColor(0.025f, 0.025f, 0.10f, 1.0f);
	
	m_DataLoader = new  RenderDataLoader();

	m_BasicShader = new SimpleShader(".\\shaders\\basic.vs.glsl", ".\\shaders\\basic.fs.glsl");
	m_DummyTexture = new SimpleTexture(SimpleTexture::Preset::DUMMY_WHITE);

	m_ScreenQuadShader = new SimpleShader(".\\shaders\\texture2screen.vs.glsl", ".\\shaders\\texture2screen.fs.glsl");

	PrepareFramebuffers(m_HDR);

	RenderData rd = m_DataLoader->GetScreenQuad();

	m_ScreenQuadVAO = rd.VAO;

	m_Skybox = m_DataLoader->GetSkyboxDesc(SkyboxPreset::DefaultSpace);


	//m_Tonemapper = new SimpleShader(".\\shaders\\tonemapping.vs.glsl", ".\\shaders\\tonemapping.fs.glsl");
	m_Tonemapper = new SimpleShader(".\\shaders\\texture2screen.vs.glsl", ".\\shaders\\tonemapping.fs.glsl");
}

Renderer::~Renderer()
{
	glDeleteFramebuffers(1, &m_Framebuffer);
}

unsigned int Renderer::GetRenderTag(ObjectPreset ps) {

	auto tagSearch = m_TagMap.find(ps);

	if (tagSearch != m_TagMap.end()) {

		return tagSearch->second;
	}
	
	RenderData rd = m_DataLoader->GetObjectData(ps);

	m_RenderDataMap[++m_TagIndex] = rd;
	m_TagMap[ps] = m_TagIndex;
	
	return static_cast<unsigned int>(m_TagIndex);

}

void Renderer::UseSkybox(SkyboxPreset sb)
{
	m_Skybox = m_DataLoader->GetSkyboxDesc(sb);
}

void Renderer::BeginFrame()
{
	m_RenderQueue.clear();
	m_LightSources.clear();

	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	m_Projection = glm::perspective(glm::radians(m_Fov), m_AspectRatio, 1.0f, 100.0f);

}

void Renderer::SetCamera(glm::vec3 position, glm::vec3 up, GLuint cameraID) {

	m_CameraPos = position;
	m_CameraUp = up;
}


void Renderer::AddToRenderQueue(const RenderRequest& rc) {

	m_RenderQueue.emplace_back(rc);

}

void Renderer::AddLightSource(LightInfo li)
{
	m_LightSources.push_back(li);
}

void Renderer::RenderFrame()
{
	
	
	if (m_HDR)
		glBindFramebuffer(GL_FRAMEBUFFER, m_HDR_Framebuffer);

	else
		glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	IMGuiMenuSetup();

	m_View = glm::lookAt(m_CameraPos, glm::vec3(0.0f, 0.0f, 0.0f), m_CameraUp);
	m_ViewProj = m_Projection * m_View * glm::mat4(1.0);
	
	for (const RenderRequest& rr : m_RenderQueue) {
		
		DrawRenderRequest(rr);
	}
	
	DrawSkybox();

	
	if (m_HDR){
		
		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, m_HDR_ScreenQuadTexture);
		
		glBindFramebuffer(GL_FRAMEBUFFER, 0);
		glBindVertexArray(m_ScreenQuadVAO);
		m_Tonemapper->Bind();
		m_Tonemapper->SetUniformFloat("exposure", 1.0f);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	else
		glBindTexture(GL_TEXTURE_2D, m_ScreenQuadTexture);
	
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindVertexArray(m_ScreenQuadVAO);
	m_ScreenQuadShader->Bind();

	glActiveTexture(GL_TEXTURE0);

	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);

	bool imguiOpen = true;
	
	if(imguiOpen){
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	glfwSwapBuffers(m_Window);
}

void Renderer::DrawRenderRequest(const RenderRequest& rr)
{
	RenderData rd = m_RenderDataMap[rr.RendererID];

	glm::mat4 modelMtx(1.0f);

	modelMtx = glm::translate(modelMtx, rr.Position);
	modelMtx = glm::rotate(modelMtx, rr.RotationAmount, rr.RotationAngle);
	modelMtx = glm::scale(modelMtx, rr.Scale);

	glActiveTexture(GL_TEXTURE0);
	
	rd.MatData.Texture->Bind();
	
	glBindVertexArray(rd.VAO);
	rd.MatData.Shader->Bind();
	rd.MatData.Shader->SetUniformMat4("viewproj", m_ViewProj);
	rd.MatData.Shader->SetUniformMat4("model", modelMtx);

	glDrawElements(GL_TRIANGLES, rd.IndexCount, GL_UNSIGNED_INT, 0);

}

void Renderer::PrepareFramebuffers(bool HDR)
{
	glGenFramebuffers(1, &m_Framebuffer);

	glBindFramebuffer(GL_FRAMEBUFFER, m_Framebuffer);

	glGenTextures(1, &m_ScreenQuadTexture);
	glBindTexture(GL_TEXTURE_2D, m_ScreenQuadTexture);

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, m_ScreenWidth, m_ScreenHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, nullptr);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_ScreenQuadTexture, 0);

	GLuint rbo;
	glGenRenderbuffers(1, &rbo);
	glBindRenderbuffer(GL_RENDERBUFFER, rbo);

	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_ScreenWidth, m_ScreenHeight);

	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rbo);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	if (HDR) {

		glGenFramebuffers(1, &m_HDR_Framebuffer);
		glBindFramebuffer(GL_FRAMEBUFFER, m_HDR_Framebuffer);

		glGenTextures(1, &m_HDR_ScreenQuadTexture);
		glBindTexture(GL_TEXTURE_2D, m_HDR_ScreenQuadTexture);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA16F, m_ScreenWidth, m_ScreenHeight, 0, GL_RGBA, GL_FLOAT, NULL);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, m_HDR_ScreenQuadTexture, 0);


		GLuint HDR_DepthStencil;
		
		glGenRenderbuffers(1, &HDR_DepthStencil);
		glBindRenderbuffer(GL_RENDERBUFFER, HDR_DepthStencil);

		glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, m_ScreenWidth, m_ScreenHeight);

		glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, HDR_DepthStencil);

		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cerr << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;

		glBindFramebuffer(GL_FRAMEBUFFER, 0);

	}

}

void Renderer::DrawSkybox()
{
	
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);
	glBindVertexArray(m_Skybox.VAO);
		
	glActiveTexture(GL_TEXTURE0);
	m_Skybox.Texture->Bind();

	m_Skybox.Shader->Bind();

	m_Skybox.Shader->SetUniformMat4("projection", m_Projection);
	m_Skybox.Shader->SetUniformMat4("view", glm::mat4(glm::mat3(m_View)));
		
	glDrawArrays(GL_TRIANGLES, 0, m_Skybox.IndexCount);
	
	glBindVertexArray(0);
	glUseProgram(0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);

	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
}

void Renderer::IMGuiMenuSetup()
{
	ImGui::Begin("Render Options", &m_Imgui_ShowRenderOptions);
	
	ImGui::Checkbox("HDR Rendering", &m_HDR);
		

	ImGui::End();

}
