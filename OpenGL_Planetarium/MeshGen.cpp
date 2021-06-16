#include "MeshGen.h"

#include "glm/glm.hpp"
#include "MathHelpers.h"
#include "GLHelpers.h"

#include <vector>
#include <iostream>


MeshDefinition MeshGen::CreateBasicCube()
{
	GLuint vaoID;

	glGenVertexArrays(1, &vaoID);

	if (vaoID == 0) {

		std::cerr << "Error! Could not generate Vertex Array Object!\n";
		return MeshDefinition{ 0, 0 };
	}

	glBindVertexArray(vaoID);

	GLuint vb;
	
	GLfloat vertices[] = {

	-0.8f, -0.8f, 0.8f,
	 0.8f, -0.8f, 0.8f,
	 0.8f,  0.8f, 0.8f,
	-0.8f,  0.8f, 0.8f,

	0.8f,  -0.8f, -0.8f,
   -0.8f,  -0.8f, -0.8f,
   -0.8f,   0.8f, -0.8f,
	0.8f,   0.8f, -0.8f

	};

	GLuint indices[]{

		// Front
		0, 1, 3,
		1, 2, 3,

		// Top
		3, 2, 6,
		2, 7, 6,

		// Left
		5, 0, 6,
		0, 3, 6,

		// Right
		1, 4, 2,
		4, 7, 2,

		// Back
		4, 5, 7,
		5, 6, 7,

		// Bottom
		0, 5, 1,
		4, 5, 1
		

	};

	glGenBuffers(1, &vb);
	glBindBuffer(GL_ARRAY_BUFFER, vb);

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
	
	glEnableVertexAttribArray(0);

	// Index Buffer

	GLuint ib;

	glGenBuffers(1, &ib);
	
	if (ib == 0) {

		std::cerr << "Error, could not create buffer \n";
		return MeshDefinition{0, 0};
	}
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
	
	return MeshDefinition{ vaoID, sizeof(indices)};
}

MeshDefinition MeshGen::CreateColoredCube()
{
	GLuint vaoID;

	glGenVertexArrays(1, &vaoID);

	if (vaoID == 0) {

		std::cerr << "Error! Could not generate Vertex Array Object!\n";
		return MeshDefinition{ 0, 0 };
	}

	glBindVertexArray(vaoID);

	float positionData[] = {

			-0.8f,  0.8f, 0.8f,
			-0.8f, -0.8f, 0.8f,
			 0.8f, -0.8f, 0.8f,
			 0.8f,  0.8f, 0.8f,

			-0.8f,  0.8f, -0.8f,
			-0.8f, -0.8f, -0.8f,
			 0.8f, -0.8f, -0.8f,
			 0.8f,  0.8f, -0.8f,

			-0.8f,  0.8f, -0.8f,
			-0.8f, -0.8f, -0.8f,
			-0.8f, -0.8f,  0.8f,
			-0.8f,  0.8f,  0.8f,

			 0.8f,  0.8f, -0.8f,
			 0.8f, -0.8f, -0.8f,
			 0.8f, -0.8f,  0.8f,
			 0.8f,  0.8f,  0.8f,

			-0.8f, 0.8f,  -0.8f,
			-0.8f, 0.8f,  0.8f,
			 0.8f, 0.8f,  0.8f,
			 0.8f, 0.8f,  -0.8f,

			-0.8f, -0.8f, -0.8f,
			-0.8f, -0.8f,  0.8f,
			 0.8f, -0.8f,  0.8f,
			 0.8f, -0.8f, -0.8f

	};

	float colorData[] = {

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,
		1.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 1.0f, 0.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,

		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f,
		0.0f, 0.0f, 1.0f
	};

	GLuint indices[] = {

		// Front face
		0, 1, 2,
		3, 0, 2,

		// Back
		6, 5, 4,
		6, 4, 7,

		// Left
		8, 9, 10,
		11, 8, 10,

		// Right
		14, 13, 12,
		14, 12, 15,

		// Top
		16, 17, 18,
		19, 16, 18,

		// Bottom
		22, 21, 20,
		22, 20, 23,

	};

	float texCoordData[]{

		0.0f, 1.0f,
		0.0f, 0.0f,
		1.0f, 0.0f,
		1.0f, 1.0f,

		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f,

		0.0f, 0.0f,
		0.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, 0.0f

	};

	GLuint vb = 0;

	glGenBuffers(1, &vb);

	if (vb == 0) {
		std::cerr << "Error, could not create array buffer \n";
		return MeshDefinition{ 0, 0 };
	}

	glBindBuffer(GL_ARRAY_BUFFER, vb);
	glBufferData(GL_ARRAY_BUFFER, sizeof(positionData), positionData, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	GLuint colorBuffer = 0;

	glGenBuffers(1, &colorBuffer);

	if (vb == 0) {
		std::cerr << "Error, could not create array buffer \n";
		return MeshDefinition{ 0, 0 };
	}

	glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(colorData), colorData, GL_STATIC_DRAW);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(1);

	GLuint ib = 0;

	glGenBuffers(1, &ib);

	if (ib == 0) {
		std::cerr << "Error, could not create vertex buffer \n";
		return MeshDefinition{ 0, 0 };
	}

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ib);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,  sizeof(indices), indices, GL_STATIC_DRAW);

	glBindVertexArray(0);

	MeshDefinition md;

	md.VAO = vaoID;
	md.IndexCount = 36;

	return md;
}

MeshDefinition MeshGen::CreateInvertedCube()
{
	return MeshDefinition();
}

MeshDefinition MeshGen::CreateBasicSphere()
{
	MeshDataUV sphereData = MeshGen::CreateGeosphere(1.0f, 3);
	
	std::vector<glm::vec3> pos;

	for (VertexUV& v : sphereData.Vertices) {
		
		pos.push_back(v.Position);
	}

	GLuint VAO = 0;

	if (!GLHelpers::CreateVAO(VAO)) {

		return MeshDefinition{ 0, 0 };
	}
	
	glBindVertexArray(VAO);

	GLuint VB = 0;

	if (!GLHelpers::CreateBuffer(VB)) {

		return MeshDefinition{ 0, 0 };
	}

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, 3*sizeof(float) * pos.size(), pos.data(), GL_STATIC_DRAW);
	

	GLuint IB = 0;

	if (!GLHelpers::CreateBuffer(IB)) {

		return MeshDefinition{ 0, 0 };
	}
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * sphereData.Indices.size(), sphereData.Indices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (const void*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	MeshDefinition md;

	md.VAO = VAO;
	md.IndexCount = sphereData.Indices.size();

	return md; 
}

MeshDefinition MeshGen::CreateColorSphere()
{
	MeshDataUV sphereData = MeshGen::CreateGeosphere(1.0f, 3);

	GLuint VAO = 0;

	if (!GLHelpers::CreateVAO(VAO)) {

		return MeshDefinition{ 0, 0 };
	}

	GLuint VB = 0;

	if (!GLHelpers::CreateBuffer(VB)) {

		return MeshDefinition{ 0, 0 };
	}

	GLuint IB = 0;

	if (!GLHelpers::CreateBuffer(IB)) {

		return MeshDefinition{ 0, 0 };
	}

	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VB);
	glBufferData(GL_ARRAY_BUFFER, sphereData.Vertices.size() * sizeof(VertexUV), sphereData.Vertices.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, sizeof(glm::vec3), GL_FLOAT, GL_FALSE, 3 * sizeof(glm::vec3) + 1 * sizeof(glm::vec2), 0);
	glVertexAttribPointer(1, sizeof(glm::vec3), GL_FLOAT, GL_FALSE, 3 * sizeof(glm::vec3) + 1 * sizeof(glm::vec2), (const void*)(sizeof(glm::vec3)));
	glVertexAttribPointer(2, sizeof(glm::vec3), GL_FLOAT, GL_FALSE, 3 * sizeof(glm::vec3) + 1 * sizeof(glm::vec2), (const void*)(2 * sizeof(glm::vec3)));
	glVertexAttribPointer(3, sizeof(glm::vec2), GL_FLOAT, GL_FALSE, 3 * sizeof(glm::vec3) + 1 * sizeof(glm::vec2), (const void*)(3 * sizeof(glm::vec3)));

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sphereData.Indices.size() * sizeof(GLuint), sphereData.Indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	MeshDefinition md; 

	md.VAO = VAO;
	md.IndexCount = sphereData.Indices.size();

	return md;

}

MeshDefinition MeshGen::CreateTexturedPlanet()
{
	
	MeshDataUV meshData = CreateGeosphere(1.0, 3); 

	std::vector<glm::vec3> pos;
	std::vector<glm::vec3> norm;
	std::vector<glm::vec2> uv;

	for (VertexUV v : meshData.Vertices) {

		pos.push_back(v.Position);
		norm.push_back(v.Normal);
		uv.push_back(v.TexC);

	}
	
	GLuint VAO;
	GLHelpers::CreateVAO(VAO);
	glBindVertexArray(VAO);

	GLuint positions;
	GLHelpers::CreateBuffer(positions);

	glBindBuffer(GL_ARRAY_BUFFER, positions);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * pos.size(), pos.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexArrayAttrib(VAO, 0);

	GLuint normals;
	GLHelpers::CreateBuffer(normals);

	glBindBuffer(GL_ARRAY_BUFFER, normals);
	glBufferData(GL_ARRAY_BUFFER, norm.size() * sizeof(glm::vec3), norm.data(), GL_STATIC_DRAW);
	
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexArrayAttrib(VAO, 1);

	GLuint TexCoords;
	GLHelpers::CreateBuffer(TexCoords);

	glBindBuffer(GL_ARRAY_BUFFER, TexCoords);
	glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec2) * uv.size(), uv.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 0, 0);
	glEnableVertexArrayAttrib(VAO, 2);

	GLuint IB;
	GLHelpers::CreateBuffer(IB);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLuint) * meshData.Indices.size(), meshData.Indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	MeshDefinition md;

	md.VAO = VAO;
	md.IndexCount = meshData.Indices.size();
	
	return md;
}

MeshDefinition MeshGen::CreateScreenQuad()
{
	GLuint VAO = 0;

	if (!GLHelpers::CreateVAO(VAO)) {

		return MeshDefinition{ 0, 0 };
	}
	
	glBindVertexArray(VAO);

	GLuint VB = 0;

	if (!GLHelpers::CreateBuffer(VB)) {

		return MeshDefinition{ 0 , 0 };
	}

	glBindBuffer(GL_ARRAY_BUFFER, VB);

	GLfloat vertices[] = {

		-1.0f, -1.0f,		0.0f, 0.0f,
		 1.0f, -1.0f,		1.0f, 0.0f,
		-1.0f,  1.0f,		0.0f, 1.0f,
		 1.0f,  1.0f,		1.0f, 1.0f

	};

	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (void*)(2 * sizeof(GLfloat)));
	
	glEnableVertexArrayAttrib(VAO, 0);
	glEnableVertexArrayAttrib(VAO, 1);
	
	MeshDefinition md;
	
	md.IndexCount = 4;
	md.VAO = VAO;

	glBindVertexArray(0);

	return md;
}

MeshDefinition MeshGen::CreateSun()
{
	MeshDataUV md = CreateGeosphere(1.0f, 4);
	
	GLuint VAO = 0;

	if (!GLHelpers::CreateVAO(VAO)) {

		return MeshDefinition{ 0, 0 };
	}

	GLuint VB = 0;

	if (!GLHelpers::CreateBuffer(VB)) {

		return MeshDefinition{ 0, 0 };
	}

	GLuint IB = 0;

	if (!GLHelpers::CreateBuffer(IB)) {

		return MeshDefinition{ 0, 0 };
	}
	
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VB);

	glBufferData(GL_ARRAY_BUFFER, md.Vertices.size() * sizeof(VertexUV), md.Vertices.data(), GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(glm::vec3) + sizeof(glm::vec2), (const void*)(0));
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(glm::vec3) + sizeof(glm::vec2), (const void*)(3*sizeof(float)));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(glm::vec3) + sizeof(glm::vec2), (const void*)(6*sizeof(float)));
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_FALSE, 3 * sizeof(glm::vec3) + sizeof(glm::vec2), (const void*)(9*sizeof(float)));
	
	glEnableVertexArrayAttrib(VAO, 0);
	glEnableVertexArrayAttrib(VAO, 1);
	glEnableVertexArrayAttrib(VAO, 2);
	glEnableVertexArrayAttrib(VAO, 3);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, md.Indices.size() * sizeof(GLuint), md.Indices.data(), GL_STATIC_DRAW);

	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER,0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	
	MeshDefinition mdef{};

	mdef.VAO = VAO;
	mdef.IndexCount = md.Indices.size();

	return mdef;

}

MeshDataUV MeshGen::CreateGeosphere(float radius, GLuint numSubDivisions) {

	// Algorhitm borrowed from Frank Luna's DX11 book. 
	numSubDivisions = std::min(numSubDivisions, 5u);

	const float X = 0.525731f;
	const float Z = 0.850651f;

	glm::vec3 pos[12]{

		glm::vec3(-X, 0.0f, Z),		glm::vec3(X, 0.0f, Z),
		glm::vec3(-X, 0.0f, -Z),	glm::vec3(X, 0.0f, -Z),
		glm::vec3(0.0f, Z, X),		glm::vec3(0.0f, Z, -X),
		glm::vec3(0.0f, -Z, X),		glm::vec3(0.0f, -Z, -X),
		glm::vec3(Z, X, 0.0f),		glm::vec3(-Z, X, 0.0f),
		glm::vec3(Z, -X, 0.0f),		glm::vec3(-Z, -X, 0.0f)
	};

	uint32_t k[60]{

		1, 4, 0,	4, 9, 0,	4, 5, 9,	 8, 5, 4,	1, 8, 4,
		1, 10, 8,	10, 3, 8,	8, 3, 5,	 3, 2, 5,	3, 7, 2,
		3, 10, 7,	10, 6, 7,	6, 11, 7,	 6, 0, 11,	6, 1, 0,
		10, 1, 6,	11, 0, 9,   2, 11, 9,	 5, 2, 9,	11, 2, 7
	};

	MeshDataUV meshData;

	meshData.Vertices.resize(12);
	meshData.Indices.resize(60);

	for (int i = 0; i < 12; ++i) {
		meshData.Vertices[i].Position = pos[i];
	}

	for (int i = 0; i < 60; ++i) {

		meshData.Indices[i] = k[i];
	}

	for (int i = 0; i < numSubDivisions; ++i) {

		Subdivide(meshData);
	}

	// Readjust vertices into a sphere formation
	for (unsigned int i = 0; i < meshData.Vertices.size(); ++i) {

		glm::vec3 n = glm::normalize(meshData.Vertices[i].Position);
		glm::vec3 p = n * radius;
	
		meshData.Vertices[i].Position = p;
		meshData.Vertices[i].Normal = n;

		float theta = MathHelpers::PolarAngleFromXY(
			meshData.Vertices[i].Position.x, meshData.Vertices[i].Position.z);

		float phi = acosf(meshData.Vertices[i].Position.y / radius);

		meshData.Vertices[i].TexC.x = theta / glm::two_pi<float>();
		meshData.Vertices[i].TexC.y = phi / glm::pi<float>();

		// Partial derivative of P with respect to theta
		// TODO: Figure out the exact math here
		meshData.Vertices[i].TangentU.x = -radius * sinf(phi) * sinf(theta);
		meshData.Vertices[i].TangentU.y = 0.0f;
		meshData.Vertices[i].TangentU.z = +radius * sinf(phi) * cosf(theta);

		meshData.Vertices[i].TangentU = glm::normalize(meshData.Vertices[i].TangentU);
	}

	return meshData;
}



// Catmull - Clark subdivision. 
// This implementation is readjusted to glm from Frank Luna's Dx11 book and its implementation
// TODO: This could probably be a bit smoother with readily sized vectors & such. 
void MeshGen::Subdivide(MeshDataUV& meshData)
{
	MeshDataUV inputCopy = meshData; 

	meshData.Vertices.resize(0);
	meshData.Indices.resize(0);

	unsigned int numTris = inputCopy.Indices.size() / 3;

	for (int i = 0; i < numTris; ++i) {

		VertexUV v0 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 0]];
		VertexUV v1 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 1]];
		VertexUV v2 = inputCopy.Vertices[inputCopy.Indices[i * 3 + 2]];

		// Midpoints
		VertexUV m0, m1, m2;

		m0.Position = glm::vec3(
			0.5f * (v0.Position.x + v1.Position.x), 
			0.5f * (v0.Position.y + v1.Position.y), 
			0.5f * (v0.Position.z + v1.Position.z));

		m1.Position = glm::vec3(
			0.5f * (v1.Position.x + v2.Position.x),
			0.5f * (v1.Position.y + v2.Position.y),
			0.5f * (v1.Position.z + v2.Position.z));

		m2.Position = glm::vec3(
			0.5f * (v0.Position.x + v2.Position.x),
			0.5f * (v0.Position.y + v2.Position.y),
			0.5f * (v0.Position.z + v2.Position.z));

		meshData.Vertices.push_back(v0);
		meshData.Vertices.push_back(v1);
		meshData.Vertices.push_back(v2);
		meshData.Vertices.push_back(m0);
		meshData.Vertices.push_back(m1);
		meshData.Vertices.push_back(m2);

		meshData.Indices.push_back(i * 6 + 0);
		meshData.Indices.push_back(i * 6 + 3);
		meshData.Indices.push_back(i * 6 + 5);

		meshData.Indices.push_back(i * 6 + 3);
		meshData.Indices.push_back(i * 6 + 4);
		meshData.Indices.push_back(i * 6 + 5);

		meshData.Indices.push_back(i * 6 + 5);
		meshData.Indices.push_back(i * 6 + 4);
		meshData.Indices.push_back(i * 6 + 2);

		meshData.Indices.push_back(i * 6 + 3);
		meshData.Indices.push_back(i * 6 + 1);
		meshData.Indices.push_back(i * 6 + 4);

	}
}
