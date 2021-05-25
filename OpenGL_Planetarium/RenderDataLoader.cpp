#include "RenderDataLoader.h"

#include <iostream>

#include "MeshGen.h"
#include "SimpleShader.h"
#include "SimpleTexture.h"


RenderDataLoader::RenderDataLoader()
{	
	//m_ObjectDefinitions.insert({ ObjectPreset::BasicCube, {MeshPreset::BasicCube, ShaderPreset::SingleColor} });
	//m_ObjectDefinitions.insert({ ObjectPreset::ColoredCube, {MeshPreset::ColoredCube, ShaderPreset::VertexColor} });
	//m_ObjectDefinitions.insert({ ObjectPreset::BasicSphere, {MeshPreset::BasicSphere, ShaderPreset::SingleColor} });
	//m_ObjectDefinitions.insert({ ObjectPreset::ColorSphere, {MeshPreset::BasicSphere, ShaderPreset::PositionColor} });
	m_ObjectDefinitions.insert({ ObjectPreset::SandPlanet, {MeshPreset::TexturedPlanet, ShaderPreset::Textured, TexturePreset::Sand} });
	m_ObjectDefinitions.insert({ ObjectPreset::Sun, {MeshPreset::Sun, ShaderPreset::Sun, TexturePreset::Sun} });

	m_ShaderPaths.insert({ ShaderPreset::SingleColor , ShaderPaths(".\\shaders\\basic.vs.glsl", ".\\shaders\\basic.fs.glsl") });
	m_ShaderPaths.insert({ ShaderPreset::VertexColor , ShaderPaths(".\\shaders\\colorvertex.vs.glsl", ".\\shaders\\colorvertex.fs.glsl") });
	m_ShaderPaths.insert({ ShaderPreset::PositionColor, ShaderPaths(".\\shaders\\positioncolor.vs.glsl", ".\\shaders\\colorvertex.fs.glsl") });
	m_ShaderPaths.insert({ ShaderPreset::Textured, ShaderPaths(".\\shaders\\textured.vs.glsl", ".\\shaders\\textured.fs.glsl") });
	m_ShaderPaths.insert({ ShaderPreset::Sun, ShaderPaths(".\\shaders\\sun.vs.glsl", ".\\shaders\\sun.fs.glsl") });

	m_TexturePaths.insert({ TexturePreset::Sand, ".\\res\\img\\perlin_sand.png" });
	m_TexturePaths.insert({ TexturePreset::Sun, ".\\res\\img\\grayscale-sun.png" });
}	

MeshDefinition RenderDataLoader::GetMeshDefinition(MeshPreset ps) {

	auto meshSearch = m_MeshMap.find(ps);

	if (meshSearch != m_MeshMap.end()) {

		return meshSearch->second;
	}
	
	else {

		return GenerateMesh(ps);
	}

}

MeshDefinition RenderDataLoader::GenerateMesh(MeshPreset ps)
{
	switch (ps) {

	case MeshPreset::BasicCube: {

		return MeshGen::CreateBasicCube();

	} break;

	/*case MeshPreset::ColoredCube: {

		return MeshGen::CreateColoredCube();
	} break;*/
	
	case MeshPreset::BasicSphere: {

		return MeshGen::CreateBasicSphere();

	} break;

	case MeshPreset::TexturedPlanet: {

		return MeshGen::CreateTexturedPlanet();

	} break;
	
	case MeshPreset::Sun: {

		return MeshGen::CreateSun();

	}

	default: {

		std::cerr << "Error: Unimplemented mesh generation request!" << std::endl;

	} break;

	}
		
	return MeshDefinition();
}



RenderData RenderDataLoader::GetObjectData(ObjectPreset obsps)
{
	auto objectDefSearch = m_ObjectDefinitions.find(obsps);

	if (objectDefSearch == m_ObjectDefinitions.end()) {

		std::cerr << "Error, object render definition not found!" << std::endl;
		return RenderData{};
	}
	
	ObjectDefinition od = objectDefSearch->second;

	MeshDefinition md = GetMeshDefinition(od.MeshPS);
	SimpleShader* shader = GetShader(od.ShaderPS);
	SimpleTexture* texture = GetTexture(od.TexturePS);

	RenderData rd;

	rd.VAO = md.VAO;
	rd.IndexCount = md.IndexCount;
	rd.MatData.Shader = shader;
	rd.MatData.Texture = texture;

	return rd;
}

SimpleShader* RenderDataLoader::GetShader(ShaderPreset shaderps)
{
	auto shaderSearch = m_ShaderMap.find(shaderps);

	if (shaderSearch != m_ShaderMap.end())
		return shaderSearch->second;


	auto shaderPathSearch = m_ShaderPaths.find(shaderps);

	if (shaderPathSearch == m_ShaderPaths.end()) {

		std::cerr << "Error, shader filepath not found" << std::endl;
		return nullptr;
	}

	return new SimpleShader(shaderPathSearch->second.VertexPath, shaderPathSearch->second.FragmentPath);
		
}

SimpleTexture* RenderDataLoader::GetTexture(TexturePreset textureps)
{
	auto textureSearch = m_TextureMap.find(textureps);

	if (textureSearch != m_TextureMap.end())
		return textureSearch->second;

	auto texturePathSearch = m_TexturePaths.find(textureps);

	if (texturePathSearch == m_TexturePaths.end()) {

		std::cerr << "Error, texture filepath not found!" << std::endl;
		return nullptr;
	}
	
	return new SimpleTexture(texturePathSearch->second);
}

