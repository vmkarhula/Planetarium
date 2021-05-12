#include "SimpleTexture.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "ext/include/stb/stb_image.h"

SimpleTexture::SimpleTexture(std::string filepath) : m_GLID(0) {

	glGenTextures(1, &m_GLID);

	if (m_GLID == 0) {

		std::cerr << "ERROR! Could not create new OpenGL texture" << std::endl;

	}

	glBindTexture(GL_TEXTURE_2D, m_GLID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	
	int width, height, nrChannels;

	unsigned char* data = stbi_load(filepath.c_str(), &width, &height, &nrChannels, 0);

	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	
	else
	{
		std::cerr << "Error! Failed to load texture at: " << filepath  << std::endl;
	}

	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
	glGenerateMipmap(GL_TEXTURE_2D);
	
	stbi_image_free(data);

}

SimpleTexture::~SimpleTexture()
{
	glDeleteTextures(1, &m_GLID);
}

void SimpleTexture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_GLID);
}
