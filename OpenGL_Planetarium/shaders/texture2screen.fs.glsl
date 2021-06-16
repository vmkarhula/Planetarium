#version 460

out vec4 FragColor;

in vec2 voutTexCoord;

uniform sampler2D screenTexture;

void main(){

    FragColor = texture(screenTexture, voutTexCoord);
}