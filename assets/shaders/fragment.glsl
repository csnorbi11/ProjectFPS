#version 430

struct Material {
    sampler2D diffuse;
    sampler2D specular;
    float shininess;
};
struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};


out vec4 FragColor;

in vec3 Normal;
in vec3 Color;
in vec2 TexCoords;
in vec3 FragPos;

uniform bool hasTexture;
uniform Material material;
uniform Light light;


uniform vec3 lightColor;
uniform vec3 lightPos;
uniform vec3 viewPos;

void main()
{
    vec3 fragResult=vec3(0.f);

    vec3 ambient = light.ambient;

    vec3 normal=normalize(Normal);
    vec3 lightDir=normalize(light.position-FragPos);
    float diff=max(dot(normal,lightDir),0);
    vec3 diffuse = light.diffuse * diff;

    float specularStrength=0.5f;
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=pow(max(dot(viewDir,reflectDir),0.f),material.shininess);
    vec3 specular = light.specular * spec;

    if(hasTexture){
        ambient*=texture(material.diffuse, TexCoords).rgb;
        diffuse*=texture(material.diffuse, TexCoords).rgb;
        specular*=texture(material.specular, TexCoords).rgb;
    }else{
        ambient*=Color;
        diffuse*=Color;
    }


    fragResult=ambient+diffuse+specular;

    FragColor=vec4(fragResult,1.f);
}