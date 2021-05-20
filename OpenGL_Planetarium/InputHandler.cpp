#include "InputHandler.h"

#include <iostream>

InputHandler::InputHandler(EventQueue* eq) :
	m_EventQueue(eq),
	m_PrevMousePos(glm::vec2(0.0, 0.0)),
	m_Mouse1_Down(false),
	m_Mouse2_Down(false)
				
{
}

void InputHandler::RegisterKeypress(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	switch (key) {

	case GLFW_KEY_SPACE: {

		std::cout << "Spacebar pressed! \n";

	} break;

	default: {
		
		std::cout << "Unrecognized keypress! \n";
	
	}

	}
}

void InputHandler::RegisterMouseClick(GLFWwindow* window, int button, int action, int mods)
{
	switch (button) {

	case GLFW_MOUSE_BUTTON_LEFT: {

		if(action == GLFW_PRESS){

		m_Mouse1_Down = true;
		
		double xpos, ypos;
		glfwGetCursorPos(window, &xpos, &ypos);

		m_PrevMousePos = glm::vec2(xpos, ypos);

		}
		else if (action == GLFW_RELEASE) {

			m_Mouse1_Down = false;

		}

	} break;

	default: {

		std::cout << "Unrecognized mouse button! \n";

	}

	}
}

void InputHandler::RegisterMouseMove(GLFWwindow* window, double xpos, double ypos)
{
	
	if (m_Mouse1_Down) {
		
		Event e{};
		
		e.Type == Event::EventType::MouseDrag;
		e.Parameters[0] = static_cast<std::byte>(xpos - m_PrevMousePos.x);
		e.Parameters[4] = static_cast<std::byte>(ypos - m_PrevMousePos.y);

		m_EventQueue->AddEvent(e);

	}
}
