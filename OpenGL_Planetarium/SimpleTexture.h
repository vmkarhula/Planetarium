#pragma once

#include <string>
#include <vector>

#include "glad/glad.h"

class SimpleTexture {

public:

	enum class Preset{DUMMY_WHITE};
	
	SimpleTexture(Preset ps);
	SimpleTexture(std::string filepath);

	// Skybox/cubemap constructor. TODO: Possibly create a class of its own for this? 
	// SimpleTexture(std::vector<std::string> skyboxpaths);
	~SimpleTexture();

	SimpleTexture(const SimpleTexture& t) = delete;
	SimpleTexture(SimpleTexture&& t) = delete;
	SimpleTexture operator=(const SimpleTexture& t) = delete;
	SimpleTexture operator=(SimpleTexture&& t) = delete;

	void Bind();
	GLuint ID() { return m_GLID; }

private:

	GLuint m_GLID; 


};