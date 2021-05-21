#include "Camera.h"

#include "glm/gtc/constants.hpp"

Camera::Camera() :
	m_Position(0.0f, 0.0f, 12.0f),
	m_Upwards(0.0f, 1.0f, 0.0f),
	m_Radius(15.0f),
	m_Theta(glm::pi<float>()),
	m_Phi(glm::half_pi<float>()){


	CalculateOrbitalCoords();
}

void Camera::AdjustRadius(float change)
{
	m_Radius -= change; 
	m_Radius = glm::clamp(m_Radius, 3.0f, 25.0f);

	CalculateOrbitalCoords(); 
}

void Camera::processMouseDrag(float x, float y)
{
	m_Theta += x;
	m_Phi += y;

	// Clamp coordinates. Allow rotation around, but not over objects. 
	if(m_Theta > glm::two_pi<float>())
		m_Theta -= glm::two_pi<float>();
		
	else if(m_Theta < 0.0f)
		m_Theta += glm::two_pi<float>();

	m_Phi = glm::clamp(m_Phi, 0.05f, glm::pi<float>() - 0.05f);

	m_Position.x = m_Radius * sinf(m_Phi) * cosf(m_Theta);
	m_Position.z = m_Radius * sinf(m_Phi) * sinf(m_Theta);
	m_Position.y = m_Radius * cosf(m_Phi);


}

void Camera::CalculateOrbitalCoords()
{
	m_Position.x = m_Radius * sinf(m_Phi) * cosf(m_Theta);
	m_Position.z = m_Radius * sinf(m_Phi) * sinf(m_Theta);
	m_Position.y = m_Radius * cosf(m_Phi);
}



