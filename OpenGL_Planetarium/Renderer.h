#pragma once

#include "glad/glad.h"
#include "MeshGen.h"

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "SimpleShader.h"
#include "SimpleTexture.h"
#include "RenderDataLoader.h"
#include "Cubemap.h"

#include <vector>
#include <unordered_map>
#include <cstddef>


/*	
	The renderer processes render requests into actual 3D render
	Renderable objects are abstracted into rendertags to the outside
*/

/* 
	RenderRequest is submitted to the renderqueue. 
	
	For now, the params is a crude way to submitting varied parameter data
	in one unified data structure. The aim is to avoid having heap allocated
	render requests that'll reduce cache performance and in general run slow with
	all the pointer chasing and such. 

	The performance isn't likely going to bite too hard in a while, but I still felt
	like experimenting a bit with more data oriented approach for the sake of learning.
*/
struct RenderRequest {
	
	glm::vec3	Position;
	glm::vec3	RotationAngle;
	float	RotationAmount;
	glm::vec3	Scale; 
	GLuint		RendererID;
	std::byte	Params[32]; 

};


// Lightinfo uses vec4s instead of vec3s as they're less problematic with GLSL memory layout
struct LightInfo {

	glm::vec4 Position;
	glm::vec4 Ambient;
	glm::vec4 Diffuse;
	glm::vec4 Specular; 

};


using RenderQueue = std::vector<RenderRequest>;


class Renderer {

public:

	Renderer();
	~Renderer();

	// No copy or assigment
	Renderer(const Renderer& rhs) = delete;
	Renderer(Renderer&& rhs) = delete;
	Renderer operator=(const Renderer& rhs) = delete;
	Renderer operator=(Renderer&& rhs) = delete;

	// GLFW uses window handle for example in input and messaging, 
	// so it is needed outside the renderer also. 
	// TODO: Figure out if some kind of clear ownership model is possible here. 
	GLFWwindow* GetWindowHandle() const { return m_Window; }
	
	unsigned int GetRenderTag(ObjectPreset ps);
	
	void UseSkybox(SkyboxPreset sb);

	void BeginFrame();

	void SetCamera(glm::vec3 position, glm::vec3 up, GLuint cameraID = 0);

	void AddToRenderQueue(const RenderRequest& rr);
	void DefineSunlight(LightInfo li);
	void RenderFrame();


private:
		
	// Maps presets into rendertags
	using TagMap = std::unordered_map<ObjectPreset, unsigned int>;

	// Transforms RenderTags into actual render data
	using RenderDataMap = std::unordered_map<GLuint, RenderData>;
		
	// Processes a single renderrequest form into a draw action
	void DrawRenderRequest(const RenderRequest& rr);

	// Helper to generate the needed framebuffers inside the class
	void PrepareFramebuffers(bool HDR = false);

	// Helper to generate the common uniformbuffers
	void PrepareUniformbuffers();

	// Updates the uniformbuffers with current data. Should be called after receiving the current scene information. 
	void UpdateUniformbuffers();

	//void BindUniformblock(SimpleShader* shader, UniformBlock block);

	// 
	void DrawSkybox();

	//
	void IMGuiMenuSetup();

private:
	
	GLFWwindow*		m_Window;
	GLuint			m_ScreenWidth;
	GLuint			m_ScreenHeight;

	RenderQueue		m_RenderQueue;
	RenderDataLoader* m_DataLoader;
	GLuint			m_Framebuffer;
	GLuint			m_ScreenQuadTexture;

	TagMap			m_TagMap;
	RenderDataMap	m_RenderDataMap;
	
	std::vector<LightInfo> m_LightSources;

	// These are usually duplicated from the scene camera, but it's probably better 
	// to avoid querying a separate memory location throughout the frame render process
	glm::vec3		m_CameraPos;
	glm::vec3		m_CameraUp;

	glm::mat4		m_Projection;
	glm::mat4		m_View;
	glm::mat4		m_ViewProj;

	float			m_Fov;
	float			m_AspectRatio;

	SimpleShader*	m_BasicShader;
	SimpleShader*	m_ScreenQuadShader;
	
	// Dummy white 1x1 texture. Can be useful for ignoring the texture on shader that takes texture input
	SimpleTexture*	m_DummyTexture;
	// TODO: Consider whether a visually noticeable debug texture (pink square pattern or so) is useful somewhere

	GLuint			m_ScreenQuadVAO;

	GLuint			m_TagIndex;

	SkyboxRenderDesc m_Skybox;

	Cubemap*		m_SkyboxTexture;
	SimpleShader*	m_SkyboxShader;

	GLuint			m_HDR_ScreenQuadTexture;
	GLuint			m_HDR_Framebuffer;
	SimpleShader*	m_Tonemapper;
	
	GLuint			m_UBMatrices;
	GLuint			m_UBSunlight;
	GLuint			m_UBBinding_Matrices;
	GLuint			m_UBBinding_SunlightDesc; 

	LightInfo		m_SunlightDesc;

	bool			m_HDR;
	bool			m_Imgui_ShowRenderOptions;

};