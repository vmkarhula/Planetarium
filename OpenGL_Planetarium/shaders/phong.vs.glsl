#version 460

in (location = 0) vPos;
in (location = 1) vNormal; 

out (location = 0) vec3 LightIntensity; 

uniform struct LightInfo{ 

    vec4 Position;
    vec3 L_ambient;
    vec3 L_diffuse;
    vec3 L_specular;

} Light;

uniform struct MaterialInfo{

    vec3 K_ambient;
    vec3 K_diffuse;
    vec3 K_specular;

    float Shininess;

} Material;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 ProjectionMatrix;
uniform mat4 MVP;

void main(){

    vec3 n = normalize( NormalMatrix * vNormal);
    vec4 camCoords = ModelViewMatrix * vec4(vertexPosition, 1.0);
    
    vec3 ambient = Light.L_ambient * Material.K_ambient;
    
    vec3 s = normalize(vec3(Light.Position - camCoords));
    float sDotN = max( dot(s,n), 0.0);
    
    vec3 diffuse = Light.L_diffuse * Material.K_diffuse * sDotN;

    vec3 spec = vec3(0.0);

    if(sDotN > 0.0 ){

        vec3 v = normalize(-camCoords.xyz);
        vec3 r = reflect( -s, n );
        spec = Light.L_specular * Material.K_specular* pow(max (dot (r, v), 0.0), Material.Shininess); 
    }
    
    LightIntensity = ambient + diffuse + spec; 
    gl_Position = MVP * vec4(vertexPosition, 1.0);
}
