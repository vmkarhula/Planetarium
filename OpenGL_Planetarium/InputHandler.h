#pragma once

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "Event.h"

// Processes input into events
class InputHandler {

public:

	// Input handler always processes input into an eventqueue. 
	// As it stands, the event queue itself is owned by the main app
	InputHandler(EventQueue* eq);

	void RegisterKeypress(GLFWwindow* window, int key, int scancode, int action, int mods);
	void RegisterMouseClick(GLFWwindow* window, int button, int action, int mods);
	void RegisterMouseMove(GLFWwindow* window, double xpos, double ypos);
	void RegisterMouseScroll(GLFWwindow* window, double xoffset, double yoffset);

private:
	
	// Previous mouse position is used in processing frame-by-frame mouse movement
	glm::vec2 m_PrevMousePos;

	EventQueue* m_EventQueue;

	// TODO: Figure out some more optimal way for this than booleans. A bitfield or such would at least pack it nicely.
	bool m_Mouse1_Down; 
	bool m_Mouse2_Down;

};