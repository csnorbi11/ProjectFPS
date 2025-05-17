#version 430

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct DirectionalLight {
    vec3 direction;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float intensity;
};
struct PointLight{
    vec3 position;
    float constant;
    float linear;
    float quadratic;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};



out vec4 FragColor;

in vec3 Normal;
in vec3 Ambient;
in vec3 Diffuse;
in vec3 Specular;
in vec2 TexCoords;
in vec3 FragPos;

uniform bool hasTexture;
uniform Material material;
uniform DirectionalLight dirLight;
#define NR_POINT_LIGHTS 4
uniform PointLight pointLights[NR_POINT_LIGHTS];
uniform int activePointLights;

uniform vec3 viewPos;

vec3 CalcDirLight(DirectionalLight light,vec3 normal,vec3 viewDir);
vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir);

void main()
{
    vec3 norm=normalize(Normal);
    vec3 viewDir=normalize(viewPos-FragPos);

    vec3 fragResult=vec3(0.f);
    fragResult=CalcDirLight(dirLight,norm,viewDir);

    for(int i=0;i<min(NR_POINT_LIGHTS,activePointLights);i++){
        fragResult+=CalcPointLight(pointLights[i],norm,FragPos,viewDir);
    }

    FragColor=vec4(fragResult,1.f);
}

vec3 CalcDirLight(DirectionalLight light,vec3 normal,vec3 viewDir){

    vec3 lightDir=normalize(-light.direction);
    float diff=max(dot(normal,lightDir),0);

    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=pow(max(dot(viewDir,reflectDir),0.f),material.shininess);

    vec3 ambient=light.ambient*Ambient;
    vec3 diffuse=light.diffuse*diff*Diffuse;
    vec3 specular=light.specular*spec*Specular;

    if(hasTexture){
        ambient*=texture(material.diffuse, TexCoords).rgb;
        diffuse*=texture(material.diffuse, TexCoords).rgb;
        specular*=texture(material.specular, TexCoords).rgb;
    }
    return light.intensity*(ambient+diffuse+specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    light.quadratic * (distance * distance));

    vec3 ambient=light.ambient*Ambient;
    vec3 diffuse=light.diffuse*Diffuse;
    vec3 specular=light.specular*Specular;

    if(hasTexture){
        ambient*=texture(material.diffuse, TexCoords).rgb;
        diffuse*=texture(material.diffuse, TexCoords).rgb;
        specular*=texture(material.specular, TexCoords).rgb;
    }
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}