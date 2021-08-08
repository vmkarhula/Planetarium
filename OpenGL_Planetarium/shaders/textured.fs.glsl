#version 460

out vec4 FragColor;

in vec2 TexCoord;
in vec3 vNormal;
in vec3 FragWPos;

/*
struct LightInfo{

    vec3 l_pos;
    vec3 l_ambient;
    vec3 l_diffuse;
    vec3 l_specular;

};
*/


//uniform LightInfo sun;

layout (std140, binding = 1) uniform LightInfo{

    vec4 l_pos;
    vec4 l_ambient;
    vec4 l_diffuse;
    vec4 l_specular;
} Sunlight;

uniform sampler2D tex1; 

void main(){

    float ambientFactor = 0.2;
    //vec3 lightColor = vec3(0.4, 0.4, 0.4);

    vec3 lightColor = Sunlight.l_diffuse.rgb;

    vec3 norm = normalize(vNormal);
    //vec3 lightDir = normalize(sun.l_pos - FragWPos);
    vec3 lightDir = normalize(Sunlight.l_pos.rgb - FragWPos);  
    //vec3 lightDir = normalize(vec3(0.0, 0.0, 0.0) - FragWPos);

    vec4 origColor =  texture(tex1, TexCoord);

    vec3 ambient = ambientFactor * origColor.rgb;

    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = vec3(diff * lightColor) *origColor.rgb;

    FragColor = vec4(ambient + diffuse, 1.0);
    
}