#pragma once

#include "Renderer.h"
#include "Camera.h"

#include "glm/glm.hpp"

#include <vector>

struct SceneObject {

	SceneObject(glm::vec3 position_, unsigned int rendertag_):
		position(position_), rotation(0.0), RenderTag(rendertag_){}

	glm::vec3 position;
	glm::vec3 rotation;

	unsigned int RenderTag; 

};

class Scene {

public: 

	enum class Preset { basic };

	// Empty Scene
	Scene();

	// Select from preset options
	Scene(Preset ps, Renderer* renderer);
	~Scene();

	// No copy or assigment 
	Scene(const Scene& rhs) = delete;
	Scene(Scene&& rhs) = delete;
	Scene operator=(const Scene& rhs) = delete;
	Scene operator=(Scene&& rhs) = delete;
	
	void Update(float dt);

	// Fills the renderqueue
	void GetRenderRequests(Renderer* renderer);

private:

	Camera						m_Camera;
	std::vector<SceneObject>	m_Objects;
	float						m_DummyRotation;

};