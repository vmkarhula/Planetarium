#pragma once

#include <string>

#include "glad/glad.h"

class SimpleTexture {

public:

	enum class Preset{DUMMY_WHITE};
	
	SimpleTexture(Preset ps);
	SimpleTexture(std::string filepath);
	~SimpleTexture();

	SimpleTexture(const SimpleTexture& t) = delete;
	SimpleTexture(SimpleTexture&& t) = delete;
	SimpleTexture operator=(const SimpleTexture& t) = delete;
	SimpleTexture operator=(SimpleTexture&& t) = delete;

	void Bind();

private:

	GLuint m_GLID; 


};