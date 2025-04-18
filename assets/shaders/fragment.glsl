#version 430

struct Material{
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
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

uniform sampler2D texture_diffuse1;

void main()
{
    vec3 fragResult=vec3(0.f);


    vec3 normal=normalize(Normal);
    vec3 lightDir=normalize(light.position-FragPos);
    float diff=max(dot(normal,lightDir),0);

    float specularStrength=0.5f;
    vec3 viewDir=normalize(viewPos-FragPos);
    vec3 reflectDir=reflect(-lightDir,normal);
    float spec=pow(max(dot(viewDir,reflectDir),0.f),material.shininess);


    vec3 ambient  = light.ambient * material.ambient;
    vec3 diffuse  = light.diffuse * (diff * material.diffuse);
    vec3 specular = light.specular * (spec * material.specular);

    fragResult=ambient+diffuse+specular;
    if(hasTexture){
        fragResult*=texture(texture_diffuse1,TexCoords).rgb;
    }else{
        fragResult*=Color;
    }

    FragColor=vec4(fragResult,1.f);
}