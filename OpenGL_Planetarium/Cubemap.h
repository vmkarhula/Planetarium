#pragma once

#include <vector>
#include <string>

#include "glad/glad.h"

class Cubemap {

public:

	Cubemap(std::vector<std::string> paths);
	~Cubemap();
	
	Cubemap(const Cubemap& rhs) = delete;
	Cubemap(Cubemap&& rhs) = delete;
	
	Cubemap operator=(const Cubemap& rhs) = delete;
	Cubemap operator=(Cubemap&& rhs) = delete;


	void Bind() { glBindTexture(GL_TEXTURE_CUBE_MAP, m_GLID); }
	GLuint ID() {return m_GLID;	}

private:

	GLuint m_GLID;

};