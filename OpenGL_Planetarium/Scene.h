#pragma once

#include "Renderer.h"
#include "Camera.h"

#include "glm/glm.hpp"

#include "Event.h"
#include "SceneNode.h"

#include <vector>
#include <memory>

/*	
	Scene is the actual simulation of the objects and their relations
	Once per frame it fills the renderqueue that'll then get renderered by the
	renderer 
*/

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
	
	void Update(float dt, EventQueue* eq = nullptr);

	// Fills the renderqueue
	void GetRenderRequests(Renderer* renderer);

private:

	void ProcessEvent(Event e);

private:

	Camera						m_Camera;
	std::vector<SceneNode>		m_Objects;
	float						m_DummyRotation;
	LightInfo					m_SunDescription;
	
	std::unique_ptr<SceneNode>	m_BaseNode;
};