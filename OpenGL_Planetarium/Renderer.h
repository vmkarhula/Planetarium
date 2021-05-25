#pragma once

#include "glad/glad.h"
#include "MeshGen.h"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "SimpleShader.h"
#include "SimpleTexture.h"
#include "RenderDataLoader.h"

#include <vector>
#include <unordered_map>
#include <cstddef>


struct RenderRequest {
		
	glm::mat4 Transform;
	GLuint RendererID;
	std::byte Params[32]; 

};


struct LightInfo {

	glm::vec3 Position;
	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular; 

};

using RenderQueue = std::vector<RenderRequest>;


class Renderer {

public:

	Renderer();
	~Renderer();

	Renderer(const Renderer& rhs) = delete;
	Renderer(Renderer&& rhs) = delete;
	Renderer operator=(const Renderer& rhs) = delete;
	Renderer operator=(Renderer&& rhs) = delete;

	// GLFW uses window handle for example in input and messaging, 
	// so it is needed outside the renderer also. 
	// TODO: Figure out if some kind of clear ownership model is possible here. 
	GLFWwindow* GetWindowHandle() { return m_Window; }
	
	unsigned int GetRenderTag(ObjectPreset ps);

	void BeginFrame();

	void SetCamera(glm::vec3 position, glm::vec3 up, GLuint cameraID = 0);

	void AddToRenderQueue(const RenderRequest& rr);
	void RenderFrame();


private:
	
	// Maps presets into rendertags
	using TagMap = std::unordered_map<ObjectPreset, unsigned int>;

	// Transforms RenderTags into actual render data
	using RenderDataMap = std::unordered_map<GLuint, RenderData>;
		
	
	void DrawRenderRequest(const RenderRequest& rr);

private:
	
	GLFWwindow*		m_Window;
	RenderQueue		m_RenderQueue;
	RenderDataLoader* m_DataLoader;

	TagMap			m_TagMap;
	RenderDataMap	m_RenderDataMap;
	
	glm::vec3		m_CameraPos;
	glm::vec3		m_CameraUp;

	glm::mat4		m_Projection;
	glm::mat4		m_View;
	glm::mat4		m_ViewProj;

	float			m_Fov;
	float			m_AspectRatio;

	SimpleShader*	m_BasicShader;
	
	// Dummy white 1x1 texture. Can be useful for ignoring the texture on shader that takes texture input
	SimpleTexture*	m_DummyTexture;
	// TODO: Consider whether a visually noticeable debug texture (pink square pattern or so) is useful somewhere

	GLuint			m_TagIndex;


};