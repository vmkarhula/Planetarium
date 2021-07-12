#include "Cubemap.h"

#include <iostream>

#include "stb/stb_image.h"

Cubemap::Cubemap(std::vector<std::string> paths)
{
	glGenTextures(1, &m_GLID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_GLID);

	int width, height, nrChannels;

	for (unsigned int i = 0; i < paths.size(); i++) {

		unsigned char* data = stbi_load(paths[i].c_str(), &width, &height, &nrChannels, 0);

		if (data) {

			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);

			stbi_image_free(data);

		}

		else {

			std::cerr << "Cubemap failed to load texture at path:" << paths[i] << std::endl;
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

Cubemap::~Cubemap()
{
	glDeleteTextures(1, &m_GLID);
}

