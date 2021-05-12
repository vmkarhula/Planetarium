#pragma once

#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Renderer.h"
#include "Scene.h"

namespace ErrorCallbacks {

	void GLFW_ErrorCallback(int error, const char* description);

	void GLAPIENTRY Callback_OpenGL_Error(GLenum source,
		GLenum type,
		GLuint id,
		GLenum severity,
		GLsizei length,
		const GLchar* message,
		const void* userParam);
}



class PlanetariumApp {

public:

	PlanetariumApp();

	bool Init();
	void Run();

private:

	GLFWwindow* m_MainWindow;
	Renderer*	m_Renderer;
	
	Scene*		m_MainScene;

	double		m_PrevTick;
	double		m_DeltaTime; 
};
