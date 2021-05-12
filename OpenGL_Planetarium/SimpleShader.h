#pragma once

#include <string>
#include <unordered_map>

#include "glad/glad.h"
#include "glm/glm.hpp"


class SimpleShader {

public:

	SimpleShader(std::string vsPath, std::string fsPath);
	~SimpleShader();

	// No copy or assigment
	SimpleShader(const SimpleShader& rhs) = delete; 
	SimpleShader(SimpleShader&& rhs) = delete;
	SimpleShader operator=(const SimpleShader& rhs) = delete; 
	SimpleShader operator=(SimpleShader&& rhs) = delete; 

	GLuint ID() { return m_GLID; }
	void Bind() { glUseProgram(m_GLID); }
	
	void SetUniformMat4(std::string uniformName, glm::mat4 val);

private:

	void CheckCompileErrors(GLuint shader, std::string type);

private: 

	GLuint m_GLID;

	std::unordered_map<std::string, GLuint> m_UniformCache;
};