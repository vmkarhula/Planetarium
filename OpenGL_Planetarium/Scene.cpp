#include "Scene.h"

#include "glm/gtc/matrix_transform.hpp"
#include "DearIMGui/imgui.h"

Scene::Scene() {}
Scene::Scene(Preset ps, Renderer* renderer) : 
	m_SunDescription({}),
	m_DrawImguiLayer(true)
{
	switch (ps) {

	case Preset::basic:
				
		m_BaseNode.reset(new Orbiter(nullptr, 0.0f, 0.0f, glm::vec3(1.0), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, 3.0f, renderer->GetRenderTag(ObjectPreset::Sun), true));
		
		SceneNode* earthlike = new Orbiter(m_BaseNode.get(), 0.05f, 8.0f, glm::vec3(1.0f, 0.0f, 0.0f), glm::vec3(1.0f, 0.0f, 0.0f), 1.0f, 0.5f, renderer->GetRenderTag(ObjectPreset::EarthlikePlanet));

		SceneNode* moon = new Orbiter(earthlike, 0.15f, 1.5f, glm::vec3(0.0f, 1.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), 1.0f, 0.15f, renderer->GetRenderTag(ObjectPreset::SandPlanet));
		earthlike->AddChild(std::unique_ptr<SceneNode>(moon));

		m_BaseNode->AddChild(std::unique_ptr<SceneNode>(earthlike));

		m_SunDescription.Position = glm::vec4(0.0f, 0.0f, 0.0f, 0.0f);
		m_SunDescription.Ambient = glm::vec4(0.2f, 0.2f, 0.2f, 0.0f);
		m_SunDescription.Diffuse = glm::vec4(0.4f, 0.4f, 0.4f, 0.0f);
		m_SunDescription.Specular = glm::vec4(0.05f, 0.05f, 0.05f, 0.0f);
		
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

	DrawImguiLayer();

}

void Scene::GetRenderRequests(Renderer* renderer)
{
	renderer->SetCamera(m_Camera.GetPos(), m_Camera.GetUpwards());
	renderer->DefineSunlight(m_SunDescription);

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

void Scene::DrawImguiLayer()
{
	ImGui::Begin("Scene Options", &m_DrawImguiLayer);
	
	ImGui::SliderFloat3("Sun Color", (float*)&m_SunDescription.Diffuse, 0.0f, 1.0f);

	ImGui::End();

}
