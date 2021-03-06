#version 460

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexNormal;
layout(location = 2) in vec3 vertexTangent;
layout(location = 3) in vec2 vertexUV;

layout (std140, binding = 0) uniform ViewProj_Matrices{

    mat4 view;
    mat4 projection;

} vp; 

//uniform mat4 viewproj;
uniform mat4 model;

out vec2 voutUV;

void main(){

    gl_Position =  vp.projection * vp.view * model *  vec4(vertexPosition, 1.0);
    //gl_Position = viewproj * model *  vec4(vertexPosition, 1.0);
    voutUV = vertexUV;
}