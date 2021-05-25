#version 460

uniform mat4 model;
uniform sampler tex1;


in (location=0) vec3 Position;
in (location=1) vec3 Normal;
in (location=2) vec3 TangentU;
in (location=3) vec2 TexC;

out (location=0) vec3 voutTexCoord;
out (location=1) vec3 voutTangentU;
out (location=2) vec3 vout ;

/* 
	glm::vec3 Position;
	glm::vec3 Normal;
	glm::vec3 TangentU;
	glm::vec2 TexC;

*/

