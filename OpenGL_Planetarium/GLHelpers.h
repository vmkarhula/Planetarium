#pragma once

#include "glad/glad.h"

#include <iostream>

namespace GLHelpers {

	bool CreateVAO(GLuint& VAO) {

		glGenVertexArrays(1, &VAO);

		if (VAO == 0) {

			std::cerr << "Error! Could not generate Vertex Array Object!\n";
			return false;
		};

		return true;
	}

	bool CreateBuffer(GLuint& Buffer){
	
		
		glGenBuffers(1, &Buffer);

		if (Buffer == 0) {

			std::cerr << "Error! Could not generate buffer object!\n";
			return false;
		};

		return true;
	}


}