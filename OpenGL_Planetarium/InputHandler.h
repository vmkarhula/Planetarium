#pragma once

#include "GLFW/glfw3.h"
#include "glm/glm.hpp"

#include "Event.h"

class InputHandler {

public:

	InputHandler(EventQueue* eq);

	void RegisterKeypress(GLFWwindow* window, int key, int scancode, int action, int mods);
	void RegisterMouseClick(GLFWwindow* window, int button, int action, int mods);
	void RegisterMouseMove(GLFWwindow* window, double xpos, double ypos);
	void RegisterMouseScroll(GLFWwindow* window, double xoffset, double yoffset);

private:

	glm::vec2 m_PrevMousePos;

	EventQueue* m_EventQueue;

	// TODO: Figure out some more optimal way for this than booleans. A bitfield or such would at least pack it nicely.
	bool m_Mouse1_Down; 
	bool m_Mouse2_Down;

};