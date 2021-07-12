#include "SimpleTexture.h"

#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "ext/include/stb/stb_image.h"

SimpleTexture::SimpleTexture(Preset ps):
	m_GLID(0)
{
	switch (ps) {

	case Preset::DUMMY_WHITE: {

		glGenTextures(1, &m_GLID);

		if (m_GLID == 0) {

			std::cerr << "ERROR! Could not create new OpenGL texture" << std::endl;

		}
		
		glBindTexture(GL_TEXTURE_2D, m_GLID);

		// TODO: Figure out if the texture settings matter here
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		unsigned char data[3];
		
		for (unsigned int i = 0; i < 3; ++i) {

			data[i] = 255;
			
		}

		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);


	} break;
	
	default: {

		std::cerr << "ERROR. Unimplemented Texture Preset! \n";
	}


	
	}
}

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

	if (data) {

		if(nrChannels == 3)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);
		}

		else if (nrChannels == 1) {

			glTexImage2D(GL_TEXTURE_2D, 0, GL_RED, width, height, 0, GL_RED, GL_UNSIGNED_BYTE, data);
			glGenerateMipmap(GL_TEXTURE_2D);

		}

	}	
	
	else
	{
		std::cerr << "Error! Failed to load texture at: " << filepath  << std::endl;
	}

	
	stbi_image_free(data);

}
/*
SimpleTexture::SimpleTexture(std::vector<std::string> skyboxpaths)
{

	glGenTextures(1, &m_GLID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_GLID);

	int width, height, nrChannels;

	for (unsigned int i = 0; i < skyboxpaths.size(); i++) {

		unsigned char* data = stbi_load(skyboxpaths[i].c_str(), &width, &height, &nrChannels, 0);

		if (data) {

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);

		}

		else {

			std::cerr << "Cubemap failed to load texture at path:" << skyboxpaths[i] << std::endl;
			stbi_image_free(data);
		}
	}

	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
}
*/

SimpleTexture::~SimpleTexture()
{
	glDeleteTextures(1, &m_GLID);
}

void SimpleTexture::Bind()
{
	glBindTexture(GL_TEXTURE_2D, m_GLID);
}
