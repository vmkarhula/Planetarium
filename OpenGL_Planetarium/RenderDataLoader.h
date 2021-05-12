#pragma once

#include "RenderPresets.h"
#include "glad/glad.h"

#include "MeshGen.h"

#include <unordered_map>
#include <string>


class SimpleShader;

// This is the main definition of a renderable object. 
// TODO: Figure out the best way to control uniforms
struct RenderData {

	GLuint VAO;
	GLuint IndexCount;
	SimpleShader* Shader;

};

// Factory for render data. 
// Doesn't manage any instances or clean anything,
// simply generates them and hands them over
class RenderDataLoader {

public:
	
	RenderDataLoader();

	RenderData GetObjectData(ObjectPreset obsps);
		
private:
		
	struct ObjectDefinition {

		MeshPreset MeshPS;
		ShaderPreset ShaderPS;

	};


	struct ShaderPaths {

		ShaderPaths(std::string vs, std::string fs): VertexPath(vs), FragmentPath(fs){}

		std::string VertexPath;
		std::string FragmentPath;

	};

	// Transforms ShaderTags into actual shader pointer; 
	using ShaderMap = std::unordered_map<ShaderPreset, SimpleShader*>;
	// 
	using MeshMap = std::unordered_map<MeshPreset, MeshDefinition>;

	// Helper functions

	// Returns a pointer to desired shader, generates a new one if one doesn't exists
	SimpleShader* GetShader(ShaderPreset shaderps);
	
	// Searches already existing meshes, calls for generatemesh if needed mesh isn't available yet
	MeshDefinition GetMeshDefinition(MeshPreset ps);
	
	// Generates mesh
	MeshDefinition GenerateMesh(MeshPreset ps);

private:

	ShaderMap		m_ShaderMap;
	MeshMap			m_MeshMap;

		// Maps object preset into individual part presets
	std::unordered_map<ObjectPreset, ObjectDefinition> m_ObjectDefinitions;

	// Maps Shader preset into actual shader code filepath
	std::unordered_map<ShaderPreset, ShaderPaths> m_ShaderPaths;
};
