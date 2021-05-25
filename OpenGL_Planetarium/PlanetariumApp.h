#pragma once

#include <string>
#include "glad/glad.h"
#include "GLFW/glfw3.h"

#include "Renderer.h"
#include "Scene.h"
#include "InputHandler.h"
#include "Event.h"

// Callback functions for GLFW and OpenGL errors
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


// Since member functions aren't viable as callbacks, these input callbacks are used to forward the input information inside the class once the app class is ready to receive input.
namespace InputCallbacks {

	static void I_MouseButtonForwarder(GLFWwindow* window, int button, int action, int mods);
	static void I_MousePositionForwarder(GLFWwindow* window, double xpos, double ypos);
	static void I_MouseScrollForwarder(GLFWwindow* window, double xoffset, double yoffset);

	static void I_KeyPressForwarder(GLFWwindow* window, int key, int scancode, int action, int mods);
	
}

// Misc information prints
namespace AppInfo {

	// Outputs the OpenGL version, device and vendor info 
	void PrintOpenGLInfo();

	// Outputs input device info
	void PrintInputDeviceInfo();

}

// The main app class. After the initial constructor and Init
// and Run calls, the interface gets called mostly for input handling. 
class PlanetariumApp {

public:

	PlanetariumApp();

	bool Init();
	void Run();

	// GLFW input is passed through these into the actual app
	void I_MouseButton(GLFWwindow* window, int button, int action, int mods);
	void I_MousePosition(GLFWwindow* window, double mouseX, double mouseY);
	void I_KeyPress(GLFWwindow* window, int key, int scancode, int action, int mods);
	void I_MouseScroll(GLFWwindow* window, double xoffset, double yoffset);

private:

	EventQueue*		m_EventQueue;

	// GLFW window is a bit of a tricky multipurpose entity. It's currently co-owned by renderer
	// and app classes. It might be worth figuring out a clean smart pointer ownership system,
	// but for now we'll just go with a raw pointers. 
	GLFWwindow*		m_MainWindow;
	
	// The rest could be updated to unique ptrs, but the ownership and lifetime are
	// quite clearly tied to the app lifetime anyway. 
	Renderer*		m_Renderer;
	
	Scene*			m_MainScene;
	InputHandler*	m_InputHandler;

	// Time management. For now, there's no need to complicate this with a separate class or so. 
	double			m_PrevTick;
	double			m_DeltaTime; 
	

};
