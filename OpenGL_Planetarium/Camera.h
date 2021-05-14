#pragma once

#include "glm/glm.hpp"

class Camera {

public:

	Camera();
		 
	glm::vec3 GetPos(){ return m_Position; }
	glm::vec3 GetUpwards(){ return m_Upwards; }
	
	void AdjustRadius(float change) { m_Radius += change; }
	void AdjustTheta(float change) { m_Theta += change; }
	void AdjustPhi(float change) { m_Phi += change; }

	void SetPos(glm::vec3 pos) { m_Position = pos; }
	//void SetTarget(glm::vec3 target);

private:

	glm::mat4 m_Projection;
	glm::vec3 m_Position;
	glm::vec3 m_Upwards; 

	// Polar coordinate system
	float m_Radius;
	float m_Phi;
	float m_Theta;
	

};