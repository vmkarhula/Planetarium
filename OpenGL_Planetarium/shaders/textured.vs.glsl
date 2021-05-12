#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord; 

uniform mat4 viewproj;
uniform mat4 model;

out vec2 TexCoord;

void main(){

    gl_Position = viewproj* model* vec4(aPos, 1.0);
    TexCoord = aTexCoord;
}

