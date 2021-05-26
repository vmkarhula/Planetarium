#version 460

layout (location=0) out vec4 FragColor;

in vec2 voutUV;

struct LightInfo{

    vec3 l_pos;
    vec3 l_ambient;
    vec3 l_diffuse;
    vec3 l_specular;

};

uniform sampler2D tex1; 
uniform vec3 color; 
uniform LightInfo sun;


void main(){

    float tone = texture(tex1, voutUV).r; 

    vec3 c1 = vec3(1, 0.345, 0.160);
    vec3 c2 = vec3(1, 0.745, 0.160);

    vec3 colorFinal = vec3(tone*c1 + ((1.0 - tone) * c2));   

    FragColor = vec4(colorFinal, 1.0); 
    
}
