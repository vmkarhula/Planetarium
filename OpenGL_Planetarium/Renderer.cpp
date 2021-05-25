#include "Renderer.h"

#include "glm/gtc/matrix_transform.hpp"
#include <iostream>

//using RenderDataLoader::RenderData;

Renderer::Renderer() :
	m_Window(nullptr),
	m_CameraPos(0.0f, 0.0f, 0.0f),
	m_CameraUp(0.0f, 1.0f, 0.0f),
	m_Fov(70.0f),
	m_AspectRatio(16.0 / 9.0),
	m_Projection(),
	m_TagIndex(0),
	m_View(),
	m_BasicShader(nullptr),
	m_DummyTexture(nullptr),
	m_DataLoader(nullptr),
	m_ViewProj()
{
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);

	m_Window = glfwCreateWindow(1280, 720, "OpenGL Planetarium", nullptr, nullptr);

	if (!m_Window) {

		std::cerr << "Error creating GLFW Window! \n";
	}

	glfwMakeContextCurrent(m_Window);
	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glCullFace(GL_BACK);
	glEnable(GL_CULL_FACE);

	glDepthFunc(GL_LESS);
	glEnable(GL_DEPTH_TEST);

	glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
	
	m_DataLoader = new  RenderDataLoader();

	m_BasicShader = new SimpleShader(".\\shaders\\basic.vs.glsl", ".\\shaders\\basic.fs.glsl");
	//m_BasicTexture = new SimpleTexture(".\\res\\img\\perlin_sand.png");
	m_DummyTexture = new SimpleTexture(SimpleTexture::Preset::DUMMY_WHITE);
}

Renderer::~Renderer()
{
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

void Renderer::BeginFrame()
{
	m_RenderQueue.clear();
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

void Renderer::RenderFrame()
{
	
	glm::mat4 view = glm::lookAt(m_CameraPos, glm::vec3(0.0f, 0.0f, 0.0f), m_CameraUp);
	//glm::mat4 model = glm::rotate(glm::mat4(1.0f))

	m_ViewProj = m_Projection * view * glm::mat4(1.0);
	

	for (const RenderRequest& rr : m_RenderQueue) {
		
		DrawRenderRequest(rr);
	}
	
	glfwSwapBuffers(m_Window);
}

void Renderer::DrawRenderRequest(const RenderRequest& rr)
{
	RenderData rd = m_RenderDataMap[rr.RendererID];

	glActiveTexture(GL_TEXTURE0);
	
	rd.MatData.Texture->Bind();
	//m_DummyTexture->Bind();

	glBindVertexArray(rd.VAO);
	rd.MatData.Shader->Bind();
	rd.MatData.Shader->SetUniformMat4("viewproj", m_ViewProj);
	rd.MatData.Shader->SetUniformMat4("model", rr.Transform);

	glDrawElements(GL_TRIANGLES, rd.IndexCount, GL_UNSIGNED_INT, 0);

}
