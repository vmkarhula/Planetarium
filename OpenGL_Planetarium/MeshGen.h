#pragma once

#include "glad/glad.h"
#include "glm/glm.hpp"

#include <unordered_map>


/* MeshGen provides various - mostly mathematically generated - meshes for the use in Planetarium.
* At this point Meshes are returned as VAO and IndexCount pairs, which is sufficient for the geometry
* as long as paired with a correct shader elsewhere. 
* 
* A lot of the code here is based on Frank Luna's DirectX11 book and then converted to OpenGL/glm-environment
* 
*/

// Using vertex array objects, this is probably all the abstraction we'll need for the
// mesh geometry itself. 
struct MeshDefinition {

	GLuint VAO;
	GLuint IndexCount;
};

// This is a general purpose vertex struct, converted directly from Frank Luna's Dx11 book examples to OpenGL & GLM. 
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

// A collection of mesh generation functions. 
// TODO: Cleanup on obsolete methods necessary at some point. 
namespace MeshGen {

	enum class Shape { Cube, Sphere };

	MeshDefinition GetGeom(Shape s);

	MeshDefinition CreateBasicCube();
	MeshDefinition CreateColoredCube();
	MeshDefinition CreateInvertedCube();
	MeshDefinition CreateBasicSphere();
	MeshDefinition CreateColorSphere();
	MeshDefinition CreateTexturedPlanet();
	MeshDefinition CreateScreenQuad();
	
	// Sun has a bit of a different shading and for now, a bit different mesh data. 
	MeshDefinition CreateSun();

	GLuint CreateSphere();

	// A OpenGL / GLM Version of Frank Luna's Geosphere generation
	// Creates a sphere with nice vertex distribution for clean shading results. 
	MeshDataUV CreateGeosphere(float radius, GLuint numSubDivisions);
	
	// Subdivide into a higher vertex count using Catmull-Clark subdivision. Used mostly by
	// the geosphere, although could be serviceable elsewhere also.  
	void Subdivide(MeshDataUV& meshData);


	
};

