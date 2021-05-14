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

namespace InputCallbacks {

	// These static classes are used to forward the input into the actual app class as soon as the app is created
	
	// TODO: Consider if more than 5 buttons are necessary (mwheel, extra buttons?)
	static void I_MouseButtonForwarder(GLFWwindow* window, int button, int action, int mods);
	static void I_MousePositionForwarder(GLFWwindow* window, double xpos, double ypos);

}

namespace AppInfo {

	// Outputs the OpenGL version, device and vendor info 
	void PrintOpenGLInfo();

	// Outputs input device info
	void PrintInputDeviceInfo();

}


class PlanetariumApp {

public:

	PlanetariumApp();

	bool Init();
	void Run();

	// GLFW input is passed through these into the actual app
	void I_MouseButton(GLFWwindow* window, int button, int action, int mods);
	void I_MousePosition(GLFWwindow* window, double mouseX, double mouseY);

private:

	GLFWwindow* m_MainWindow;
	Renderer*	m_Renderer;
	
	Scene*		m_MainScene;

	double		m_PrevTick;
	double		m_DeltaTime; 
};
