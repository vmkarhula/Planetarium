#include "Scene.h"

#include "glm/gtc/matrix_transform.hpp"

Scene::Scene() {}
Scene::Scene(Preset ps, Renderer* renderer) : m_DummyRotation(0.0f)
{
	switch (ps) {

	case Preset::basic:
				
		m_Objects.emplace_back(
			SceneObject(glm::vec3(0.0f, 0.0f, 0.0f),
				renderer->GetRenderTag(ObjectPreset::TexturedPlanet)));

		m_Objects.emplace_back(
			SceneObject(glm::vec3(0.0f, 0.0f, 0.0f),
				renderer->GetRenderTag(ObjectPreset::BasicSphere)));

	}
}
Scene::~Scene()
{
};

void Scene::Update(float dt)
{
	m_Objects[0].rotation.y += 2.0f * dt;
	m_Objects[0].rotation.x += 2.0f * dt;

	m_DummyRotation += dt;
	
	if (m_DummyRotation > glm::two_pi<float>()) {

		m_DummyRotation -= glm::two_pi<float>();
	}

	m_Objects[0].position.x = 8.0f * glm::cos(m_DummyRotation);
	m_Objects[0].position.z = 8.0f * glm::sin(m_DummyRotation);


	if (m_Objects[0].rotation.y <= 0.0f) {
		m_Objects[0].rotation.y += 360.0f;
	}

	else if (m_Objects[0].rotation.y >= 360.0f) {
		m_Objects[0].rotation.y -= 360.0f;
	}
}

void Scene::GetRenderRequests(Renderer* renderer)
{
	renderer->SetCamera(m_Camera.GetPos(), m_Camera.GetUpwards());

	// For each space partition, get object render data
	for (const SceneObject& obj : m_Objects) {	
		
		glm::mat4 model = glm::mat4(1.0);

		model = glm::translate(model, obj.position);
		model = glm::rotate(model, obj.rotation.y, glm::vec3(1.0f, 1.0f, 0.0f));
		
		renderer->AddToRenderQueue(RenderRequest{ model, obj.RenderTag });
	}
}
