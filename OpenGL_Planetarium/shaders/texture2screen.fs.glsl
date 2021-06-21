#version 460

out vec4 FragColor;

in vec2 voutTexCoord;

uniform sampler2D screenTexture;


const float offset = 1.0 / 300.0;  

void main()
{
    FragColor = texture(screenTexture, voutTexCoord);
}  
