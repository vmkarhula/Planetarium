#pragma once

#include "glm/glm.hpp"

class Camera {

public:

	Camera();
	glm::vec3 GetPos(){ return m_Position; }
	glm::vec3 GetUpwards(){ return m_Upwards; }
	
private:

	glm::mat4 m_Projection;
	glm::vec3 m_Position;
	glm::vec3 m_Upwards; 


};