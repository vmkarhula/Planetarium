#include "Scene.h"

#include "glm/gtc/matrix_transform.hpp"

Scene::Scene() {}
Scene::Scene(Preset ps, Renderer* renderer) : 
	m_DummyRotation(0.0f), 
	m_SunDescription({})
{
	switch (ps) {

	case Preset::basic:
				
		m_BaseNode.reset(new Orbiter(nullptr, 0.0f, 0.0f, glm::vec3(1.0), glm::vec3(0.0), 3.0f, renderer->GetRenderTag(ObjectPreset::Sun)));
		
		/*
		m_Objects.emplace_back(
			SceneNode(glm::vec3(0.0f, 0.0f, 0.0f), 3.0f,
				renderer->GetRenderTag(ObjectPreset::Sun)));

		m_Objects.emplace_back(
			SceneNode(glm::vec3(0.0f, 0.0f, 0.0f), 0.8f, 
				renderer->GetRenderTag(ObjectPreset::SandPlanet)));

		m_Objects.emplace_back(
			SceneNode(glm::vec3(0.0f, 0.0f, 0.0f), 1.3f,
				renderer->GetRenderTag(ObjectPreset::EarthlikePlanet)));
			
		*/

		m_SunDescription.Position = glm::vec3(0.0f, 0.0f, 0.0f);
		m_SunDescription.Ambient = glm::vec3(0.2f, 0.2f, 0.2f);
		m_SunDescription.Diffuse = glm::vec3(0.4f, 0.4f, 0.4f);
		m_SunDescription.Specular = glm::vec3(0.05f, 0.05f, 0.05f);

		
	}
}
Scene::~Scene()
{
};

void Scene::Update(float dt, EventQueue* eq)
{
	m_BaseNode->Update(dt);
	
	if (eq) {

		while (!eq->Empty())
			ProcessEvent(eq->Pop());

	}
	/*
	m_Objects[0].rotation.y += 2.0f * dt;
	m_Objects[0].rotation.x += 2.0f * dt;

	m_DummyRotation += dt;
	
	if (m_DummyRotation > glm::two_pi<float>()) {

		m_DummyRotation -= glm::two_pi<float>();
	}

	m_Objects[1].position.x = 8.0f * glm::cos(m_DummyRotation);
	m_Objects[1].position.z = 8.0f * glm::sin(m_DummyRotation);

	m_Objects[1].rotation.y += 2.0f * dt;
	m_Objects[1].rotation.x += 2.0f * dt;


	if (m_Objects[1].rotation.y <= glm::two_pi<float>()) {
		m_Objects[1].rotation.y += glm::two_pi<float>();
	}

	else if (m_Objects[1].rotation.y >= glm::two_pi<float>()) {
		m_Objects[1].rotation.y -= glm::two_pi<float>();
	}

	
	m_Objects[2].position.x = 12.0f * glm::cos(m_DummyRotation + glm::half_pi<float>());
	m_Objects[2].position.z = 12.0f * glm::sin(m_DummyRotation + glm::half_pi<float>());

	m_Objects[2].rotation.y += 2.0f * dt;
	m_Objects[2].rotation.x += 2.0f * dt;


	if (m_Objects[2].rotation.y <= 0.0f) {
		m_Objects[2].rotation.y += glm::two_pi<float>();
	}

	else if (m_Objects[2].rotation.y >= glm::two_pi<float>()) {
		m_Objects[2].rotation.y -= glm::two_pi<float>();
	}
	*/
}

void Scene::GetRenderRequests(Renderer* renderer)
{
	renderer->SetCamera(m_Camera.GetPos(), m_Camera.GetUpwards());
	renderer->AddLightSource(m_SunDescription);

	// For each space partition, get object render data
	/*for (const SceneNode& obj : m_Objects) {	
		
		glm::mat4 model = glm::mat4(1.0);

		model = glm::translate(model, obj.position);
		model = glm::scale(model, obj.scale * glm::vec3(1.0));
		model = glm::rotate(model, obj.rotation.y, glm::vec3(1.0f, 1.0f, 0.0f));
				
		renderer->AddToRenderQueue(RenderRequest{ model, obj.RenderTag });
	}*/

	m_BaseNode->GetRenderRequest(renderer);
}

void Scene::ProcessEvent(Event e)
{
	switch (e.Type) {

	case Event::EventType::MouseDrag: {

		float x = e.p1;
		float y = e.p2;

		m_Camera.processMouseDrag(x, y);

	} break;
	
	case Event::EventType::Scroll: {

		m_Camera.AdjustRadius(e.p2);
	} break;

	}
}
