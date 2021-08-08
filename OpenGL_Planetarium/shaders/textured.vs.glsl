#version 460

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoord; 

layout (location = 0) out vec2 TexCoord;
layout (location = 1) out vec3 vNormal;
layout (location = 2) out vec3 FragWPos; 

layout (std140, binding = 0) uniform ViewProj_Matrices{

    mat4 view;
    mat4 projection;

} vp; 

uniform mat4 viewproj;
uniform mat4 model;


void main(){

    gl_Position = vp.projection * vp.view * model* vec4(aPos, 1.0);
    TexCoord = aTexCoord;
    vNormal = mat3(transpose(inverse(model))) * aNormal;  
    FragWPos = vec3(model * vec4(aPos, 1.0));
}

