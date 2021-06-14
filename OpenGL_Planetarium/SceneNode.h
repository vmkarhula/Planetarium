#pragma once

#include "Renderer.h"
#include <vector>
#include <memory>

class SceneNode {

public:

	SceneNode(glm::vec3 position, SceneNode* parent, int renderTag);
	virtual ~SceneNode() = default;

	SceneNode(const SceneNode& rhs) = delete; 
	SceneNode(SceneNode&& rhs) = delete;
	SceneNode operator=(const SceneNode& rhs) = delete;
	SceneNode operator=(SceneNode& rhs) = delete; 

	virtual void Update(float dt) = 0;
	virtual void GetRenderRequest(Renderer* renderer) = 0;

	virtual void AddChild(std::unique_ptr<SceneNode>&& node) = 0;
	
	glm::vec3 Position() const { return m_Position; }
	int	ID() const { return m_NodeID; }

protected:

	static int				m_IDCounter;
	int						m_NodeID; 
	int						m_RenderTag;
	glm::vec3				m_Position;
	SceneNode*				m_Parent; 
	std::vector<std::unique_ptr<SceneNode>> m_Children;
	
};


class Orbiter : public SceneNode {

public: 
	struct BuildData {
		

	};


	Orbiter(SceneNode* parent, float orbitSpeed, float orbitRadius, glm::vec3 orbitAxis, glm::vec3 spinAngle, float spinSpeed, float scale, int m_RenderTag, bool drawDebugMenu = false);
	
	Orbiter(const Orbiter& lhs) = delete;
	Orbiter(Orbiter&& lhs) = delete;
	Orbiter operator=(const Orbiter& rhs) = delete;
	Orbiter operator=(Orbiter&& rhs) = delete; 

	
	//Orbiter(BuildData);
	virtual ~Orbiter() = default;



	void Update(float dt) override;
	void GetRenderRequest(Renderer* renderer) override;
	
	void AddChild(std::unique_ptr<SceneNode>&& node) override; 

private: 

	void CalculatePosition();

private:

	float m_OrbitSpeed;
	float m_OrbitRadius;
	float m_OrbitPos;
	glm::vec3 m_OrbitAxis; 
	glm::vec3 m_Scale; 
	glm::vec3 m_SpinAngle;
	float m_SpinValue;
	bool m_DrawDebugMenu;
};