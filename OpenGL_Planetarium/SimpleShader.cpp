#include "SimpleShader.h"

#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

#include "glm/gtc/type_ptr.hpp"

SimpleShader::SimpleShader(std::string vsPath, std::string fsPath) :
	m_GLID(0)
{

	// Extract shader code from file to this string
	std::string vsCodeString; 
	
	{
		std::ifstream vsRead(vsPath);

		if (!vsRead) {
			std::cerr << "Error, could not open vertex shader file! \n";
			return;
		}

		std::stringstream vsStream;
		vsStream << vsRead.rdbuf();
		vsRead.close();

		vsCodeString = vsStream.str();

	}

	if (vsCodeString.empty()) {
		std::cerr << "Error reading the vertex shader code string! \n";
		return;
	}

	std::string fsCodeString;

	{
		std::ifstream fsRead(fsPath);

		if (!fsRead) {
			std::cerr << "Error, could not open fragment shader file! \n";
			return;
		}

		std::stringstream fsStream;
		fsStream << fsRead.rdbuf();
		fsRead.close();

		fsCodeString = fsStream.str();

	}

	if (fsCodeString.empty()) {
		std::cerr << "Error reading the fragment shader code string! \n";
		return;
	}

	GLuint vertex, fragment; 

	// Create the GL shaders, attach the shader strings to them 
	vertex = glCreateShader(GL_VERTEX_SHADER);
	fragment = glCreateShader(GL_FRAGMENT_SHADER);

	const char* vertexCstr = vsCodeString.c_str();
	const char* fragmentCstr = fsCodeString.c_str();

	// Attempt to compile the shaders
	glShaderSource(vertex, 1, &vertexCstr, nullptr);
	glCompileShader(vertex);
	CheckCompileErrors(vertex, "VERTEX");


	glShaderSource(fragment, 1, &fragmentCstr, nullptr);
	glCompileShader(fragment);
	CheckCompileErrors(fragment, "FRAGMENT");

	// Link the compiled shaders into program
	// For now, separable shaders are not used
	m_GLID = glCreateProgram();
	glAttachShader(m_GLID, vertex);
	glAttachShader(m_GLID, fragment);

	glLinkProgram(m_GLID);
	
	CheckCompileErrors(m_GLID, "PROGRAM");

	// Cleanup
	glDeleteShader(vertex);
	glDeleteShader(fragment);

}

SimpleShader::~SimpleShader()
{
	glDeleteProgram(m_GLID);
}

void SimpleShader::SetUniformMat4(std::string uniformName, glm::mat4 val)
{
	// Query the uniform location cache
	auto locationQuery = m_UniformCache.find(uniformName);
	GLuint uniformLoc;

	// If the uniform location isn't in the cache yet
	if (locationQuery == m_UniformCache.end()) {

		GLint query = glGetUniformLocation(m_GLID, uniformName.c_str());

		if (query == -1) {

			std::cerr << "Error, queried uniform: " << "\"" << uniformName << "\"" <<  " not found!" << std::endl;
			return;
		}
		
		else {

			// Found the location, update cache
			uniformLoc = static_cast<GLuint>(query);
			m_UniformCache[uniformName] = uniformLoc;
		}		
		
	}

	else {

		uniformLoc = locationQuery->second;	
	}
	
	// All good, update the value to the actual shader program
	glUniformMatrix4fv(uniformLoc, 1, GL_FALSE, glm::value_ptr(val));
}

void SimpleShader::SetUniformFloat(std::string uniformName, glm::float32 val)
{
	auto locationQuery = m_UniformCache.find(uniformName);
	GLuint uniformLoc;

	// If the uniform location isn't in the cache yet
	if (locationQuery == m_UniformCache.end()) {

		GLint query = glGetUniformLocation(m_GLID, uniformName.c_str());

		if (query == -1) {

			std::cerr << "Error, queried uniform: " << "\"" << uniformName << "\"" << " not found!" << std::endl;
			return;
		}

		else {

			// Found the location, update cache
			uniformLoc = static_cast<GLuint>(query);
			m_UniformCache[uniformName] = uniformLoc;
		}

	}

	else {

		uniformLoc = locationQuery->second;
	}

	glUniform1f(uniformLoc, val);
}

void SimpleShader::SetLightParameter(std::string uniformName, LightInfo val)
{
	
}

// Error check based of OpenGL cookbook by David Wolff
void SimpleShader::CheckCompileErrors(GLuint shader, std::string type)
{

	GLint success;
	GLchar infoLog[1024];

	// Individual shader compilation status
	if (type != "PROGRAM") {

		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success) {

			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR! Shader compilation failed: " << type << "\n" << infoLog << std::endl;

		}
	}

	// Shader program linking status
	else {
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "Error! Shader linking failed!: " << infoLog << std::endl;
		}
	}
}
