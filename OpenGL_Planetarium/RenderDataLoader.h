#pragma once

#include "RenderPresets.h"
#include "glad/glad.h"

#include "MeshGen.h"

#include <unordered_map>
#include <string>


class SimpleShader;
class SimpleTexture;

struct MatProperties {

	glm::vec3 Ambient;
	glm::vec3 Diffuse;
	glm::vec3 Specular; 
	float Shininess;
};

struct MaterialDesc {

	ShaderPreset ShaderPS;
	TexturePreset SamplerPS;

	MatProperties MatProp;

};

struct MaterialData {

	SimpleShader* Shader;
	SimpleTexture* Texture;

	MatProperties MatProp;
};



// This is the main definition of a renderable object. 
// TODO: Figure out the best way to control uniforms
struct RenderData {

	GLuint VAO;
	GLuint IndexCount;
	MaterialData MatData;

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
		TexturePreset TexturePS;
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

	using TextureMap = std::unordered_map<TexturePreset, SimpleTexture*>;
	// Helper functions

	// Returns a pointer to desired shader, generates a new one if one doesn't exists
	SimpleShader* GetShader(ShaderPreset shaderps);
	
	SimpleTexture* GetTexture(TexturePreset textureps);

	// Searches already existing meshes, calls for generatemesh if needed mesh isn't available yet
	MeshDefinition GetMeshDefinition(MeshPreset ps);
	
	// Generates mesh
	MeshDefinition GenerateMesh(MeshPreset ps);


private:

	// These are populated as data is requested and generated
	ShaderMap		m_ShaderMap;
	MeshMap			m_MeshMap;
	TextureMap		m_TextureMap;

	// These are populated at class instance construction
	// 
	// Maps object preset into individual part presets
	std::unordered_map<ObjectPreset, ObjectDefinition> m_ObjectDefinitions;

	// Maps Shader preset into actual shader code filepath
	std::unordered_map<ShaderPreset, ShaderPaths> m_ShaderPaths;
	std::unordered_map<TexturePreset, std::string> m_TexturePaths;
	
};
