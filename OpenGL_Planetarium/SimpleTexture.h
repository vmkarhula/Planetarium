#pragma once

#include <string>
#include <vector>

#include "glad/glad.h"

class SimpleTexture {

public:

	enum class Preset{DUMMY_WHITE};
	
	// For code generated textures and such
	SimpleTexture(Preset ps);

	// For textures loaded from file
	SimpleTexture(std::string filepath);
		
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