#version 430

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};
struct TextureMaterial {
    sampler2D diffuse;
    sampler2D specular;
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
in vec2 TexCoords;
in vec3 Tangent;
in vec3 FragPos;

uniform bool hasTexture;
uniform TextureMaterial texMat;
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
        //fragResult+=CalcPointLight(pointLights[i],norm,FragPos,viewDir);
    }

    FragColor=vec4(fragResult,1.f);
}

vec3 CalcDirLight(DirectionalLight light,vec3 normal,vec3 viewDir){

    vec3 lightDir=normalize(-light.direction);
    float diff=max(dot(normal,lightDir),0);

    vec3 halfway= normalize(lightDir + viewDir);
    float spec=pow(max(dot(normal,halfway),0.f),material.shininess);

    vec3 ambient=light.ambient*material.ambient;
    vec3 diffuse=light.diffuse*diff*material.diffuse;
    vec3 specular=light.specular*spec*material.specular;

    if(hasTexture){
        ambient*=texture(texMat.diffuse, TexCoords).rgb;
        diffuse*=texture(texMat.diffuse, TexCoords).rgb;
        specular*=texture(texMat.specular, TexCoords).rgb;
    }
    return light.intensity*(ambient+diffuse+specular);
}

vec3 CalcPointLight(PointLight light, vec3 normal, vec3 fragPos, vec3 viewDir)
{
    vec3 lightDir = normalize(light.position - fragPos);
    float diff = max(dot(normal, lightDir), 0.0);

    vec3 halfway= normalize(lightDir + viewDir);
    float spec=pow(max(dot(normal,halfway),0.f),material.shininess);

    float distance    = length(light.position - fragPos);
    float attenuation = 1.0 / (light.constant + light.linear * distance +
    light.quadratic * (distance * distance));

    vec3 ambient=light.ambient*material.ambient;
    vec3 diffuse=light.diffuse*diff*material.diffuse;
    vec3 specular=light.specular*spec*material.specular;

    if(hasTexture){
        ambient*=texture(texMat.diffuse, TexCoords).rgb;
        diffuse*=texture(texMat.diffuse, TexCoords).rgb;
        specular*=texture(texMat.specular, TexCoords).rgb;
    }
    ambient  *= attenuation;
    diffuse  *= attenuation;
    specular *= attenuation;
    return (ambient + diffuse + specular);
}