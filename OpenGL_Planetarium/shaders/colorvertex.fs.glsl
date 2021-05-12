#version 460

layout (location=0) in vec3 voutColor;

layout (location=0) out vec4 fragColor;

void main(){

    fragColor = vec4(voutColor, 1.0);
}