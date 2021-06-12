#pragma once

#include "SceneNode.h"

#include "glm/gtc/constants.hpp"
#include "DearIMGui/imgui.h"

#include "MathHelpers.h"


int SceneNode::m_IDCounter = 1;

SceneNode::SceneNode(glm::vec3 position_, SceneNode* parent_, int renderTag_) :
	m_NodeID(0),
	m_RenderTag(renderTag_),
	m_Position(position_),
	m_Parent(parent_)
{
	m_NodeID = m_IDCounter++;
}

Orbiter::Orbiter(SceneNode* parent, float orbitSpeed, float orbitRadius, glm::vec3 orbitAxis, glm::vec3 spin, float scale, int renderTag, bool drawDebugMenu):

	SceneNode(glm::vec3(0.0f), parent, renderTag),
	m_OrbitSpeed(orbitSpeed),
	m_OrbitPos(0.0f),
	m_OrbitRadius(orbitRadius),
	m_OrbitAxis(orbitAxis),
	m_Scale(scale),
	m_Spin(spin),
	m_DrawDebugMenu(drawDebugMenu)
{
	CalculatePosition();
}

void Orbiter::Update(float dt)
{
	glm::vec3 parentPos = glm::vec3(0.0f);

	if(m_Parent)
		parentPos = m_Parent->Position();

	
	m_Spin.y += 2.0f * dt;
	
	MathHelpers::NormalizeRotation(m_Spin, 0.0f, glm::two_pi<float>());

	
	if(m_DrawDebugMenu){
		
		ImGui::Begin("Another Window", &m_DrawDebugMenu);   // Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Text("Hello from another window!");
		ImGui::End();
	}


	/*
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

	*/



	for (std::unique_ptr<SceneNode>& child : m_Children) {

		child->Update(dt);

	}
}

void Orbiter::GetRenderRequest(Renderer* renderer)
{
	RenderRequest rr;
	rr.RendererID	=	m_RenderTag;
	rr.Rotation		=	m_Spin;
	rr.Scale		=	m_Scale;
	rr.Position		=	m_Position;

	renderer->AddToRenderQueue(rr);

	for (std::unique_ptr<SceneNode>& child : m_Children) {

		child->GetRenderRequest(renderer);
	}

}

void Orbiter::AddChild(std::unique_ptr<SceneNode> node)
{
	m_Children.push_back(std::move(node));
}

void Orbiter::CalculatePosition()
{
}
