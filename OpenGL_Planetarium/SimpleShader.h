#pragma once

#include <string>
#include <unordered_map>
#include "Renderer.h"

#include "glad/glad.h"
#include "glm/glm.hpp"


class SimpleShader {

public:

	// For now, the construction simply takes in filepaths for the shader code in text form.
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
	void SetUniformFloat(std::string uniformName, glm::float32 val);

	void SetLightParameter(std::string uniformName, LightInfo val);

private:

	// Internal check for compiler errors. Outputs text to cerr
	void CheckCompileErrors(GLuint shader, std::string type);

private: 

	GLuint m_GLID;
	
	// Cache to avoid querying OpenGL for uniform locations every frame 
	std::unordered_map<std::string, GLuint> m_UniformCache;
};