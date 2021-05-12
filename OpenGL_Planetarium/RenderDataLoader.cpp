#include "RenderDataLoader.h"

#include <iostream>

#include "MeshGen.h"
#include "SimpleShader.h"


RenderDataLoader::RenderDataLoader()
{	
	m_ObjectDefinitions.insert({ ObjectPreset::BasicCube, {MeshPreset::BasicCube, ShaderPreset::SingleColor} });
	//m_ObjectDefinitions.insert({ ObjectPreset::ColoredCube, {MeshPreset::ColoredCube, ShaderPreset::VertexColor} });
	m_ObjectDefinitions.insert({ ObjectPreset::BasicSphere, {MeshPreset::BasicSphere, ShaderPreset::SingleColor} });
	m_ObjectDefinitions.insert({ ObjectPreset::ColorSphere, {MeshPreset::BasicSphere, ShaderPreset::PositionColor} });
	m_ObjectDefinitions.insert({ ObjectPreset::TexturedPlanet, {MeshPreset::TexturedPlanet, ShaderPreset::Textured} });

	m_ShaderPaths.insert({ ShaderPreset::SingleColor , ShaderPaths(".\\shaders\\basic.vs.glsl", ".\\shaders\\basic.fs.glsl") });
	m_ShaderPaths.insert({ ShaderPreset::VertexColor , ShaderPaths(".\\shaders\\colorvertex.vs.glsl", ".\\shaders\\colorvertex.fs.glsl") });
	m_ShaderPaths.insert({ ShaderPreset::PositionColor, ShaderPaths(".\\shaders\\positioncolor.vs.glsl", ".\\shaders\\colorvertex.fs.glsl") });
	m_ShaderPaths.insert({ ShaderPreset::Textured, ShaderPaths(".\\shaders\\textured.vs.glsl", ".\\shaders\\textured.fs.glsl") });
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
	
	RenderData rd;

	rd.VAO = md.VAO;
	rd.IndexCount = md.IndexCount;
	rd.Shader = shader;

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

