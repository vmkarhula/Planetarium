#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"



#include <unordered_map>

struct MeshDefinition {

	GLuint VAO;
	GLuint IndexCount;
};

struct VertexUV {

	VertexUV() {}
	VertexUV(const glm::vec3& p, const glm::vec3& n, const glm::vec3& t, const glm::vec2& uv) :
		Position(p), Normal(n), TangentU(t), TexC(uv) {}
	VertexUV(
		float px, float py, float pz,
		float nx, float ny, float nz,
		float tx, float ty, float tz,
		float u, float v)
		: Position(px, py, pz), Normal(nx, ny, nz), TangentU(tx, ty, tz), TexC(u, v) {}

	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 TangentU;
	glm::vec2 TexC;
};

struct VertexRGB {

	VertexRGB() {}
	VertexRGB(const glm::vec3& p, const glm::vec3& n, const glm::vec3& t, const glm::vec3& c) :
		Position(p), Normal(n), TangentU(t), Color(c) {}
	VertexRGB(
		float px, float py, float pz,
		float nx, float ny, float nz,
		float tx, float ty, float tz,
		float cr, float cg, float cb)
		: Position(px, py, pz), Normal(nx, ny, nz), TangentU(tx, ty, tz), Color(cr, cg, cb) {}

	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 TangentU;
	glm::vec3 Color;
};


struct MeshDataUV {

	std::vector<VertexUV> Vertices;
	std::vector<unsigned int> Indices;

};

struct MeshDataRGB {

	std::vector<VertexRGB> Vertices;
	std::vector<unsigned int> Indicdes;

};


namespace MeshGen {

	enum class Shape { Cube, Sphere };

	MeshDefinition GetGeom(Shape s);

	MeshDefinition CreateBasicCube();
	MeshDefinition CreateColoredCube();
	MeshDefinition CreateInvertedCube();
	MeshDefinition CreateBasicSphere();
	MeshDefinition CreateColorSphere();
	MeshDefinition CreateTexturedPlanet();

	GLuint CreateSphere();

	MeshDataUV CreateGeosphere(float radius, GLuint numSubDivisions);
	
	// Subdivide into a higher vertex count using Catmull-Clark subdivision
	void Subdivide(MeshDataUV& meshData);


	
};

