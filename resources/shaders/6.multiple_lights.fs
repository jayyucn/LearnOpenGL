#version 330 core

out vec4 FragColor;

struct DirLight{
    vec3 direction;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}

struct PointLight{
    vec3 position;

    float constant;
    float linear;
    float quadradic;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}

struct SpotLight{
    vec3 position;
    vec3 direction;
    float cutoff;
    float outerCutoff;

    float constant;
    float linear;
    float specular;

    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
}

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shinniness;
}

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

#define NR_POINT_LIGHTS 4

uniform DirLight dirLight;
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform SpotLight spotLight;
uniform Material material;

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir);

void main()
{

}

vec3 CalcDirLight(DirLight light, vec3 normal, vec3 viewDir)
{
    vec3 lightDir = normalize(-light.direction);
    float diff = max(dot(normal, lightDir), 0.0);
    

}