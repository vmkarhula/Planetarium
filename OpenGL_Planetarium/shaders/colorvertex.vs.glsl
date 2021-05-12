#version 460

layout (location=0) in vec3 vertexPosition;
layout (location=1) in vec3 vinColor;

uniform mat4 viewproj;
uniform mat4 model;

out vec3 voutColor;

void main(){

    voutColor = vinColor;
    gl_Position = viewproj * model * vec4(vertexPosition, 1.0);

}