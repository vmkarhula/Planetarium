#pragma once

#include "RenderPresets.h"
#include "glad/glad.h"

#include "MeshGen.h"

#include <unordered_map>
#include <string>

/* RenderDataLoader is a database for vertexdata and shaders that the program has loaded or can load
*  The aim is to abstract away as much of the loading process from the renderer itself and to avoid loading duplicated
*  instances of meshes or shaders whenever possible. 
* 
*  As it stands, it's a constantly work in progress as more renderer features and more complex mixes of render
*  elements are added. At some point a proper rewrite is probably necessary to reduce clutter.
* 
*  The plan is to bring in some XML definitions to reduce the clutter on C++ side of things. 
*/

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
	
	// Returns a simple setup for drawing a texture on the screen
	RenderData GetScreenQuad();

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

	RenderData		m_ScreenQuadRD; 

	// These are populated at class instance construction
	// 
	// Maps object preset into individual part presets
	std::unordered_map<ObjectPreset, ObjectDefinition> m_ObjectDefinitions;

	// Maps Shader preset into actual shader code filepath
	std::unordered_map<ShaderPreset, ShaderPaths> m_ShaderPaths;
	std::unordered_map<TexturePreset, std::string> m_TexturePaths;
	
};
