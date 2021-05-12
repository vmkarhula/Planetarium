#version 460

layout (location=0) in vec3 vertexPosition;

uniform mat4 viewproj;
uniform mat4 model;

out vec3 voutColor;

void main(){

    voutColor = vertexPosition;    
    gl_Position = viewproj * model * vec4(vertexPosition, 1.0);

}