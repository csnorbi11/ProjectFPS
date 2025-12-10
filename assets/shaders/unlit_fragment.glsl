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


out vec4 FragColor;

in vec2 TexCoords;
in vec3 FragPos;

uniform bool hasTexture;
uniform TextureMaterial texMat;
uniform Material material;




void main()
{
    vec3 fragResult;

    vec3 ambient=material.ambient;
    vec3 diffuse=material.diffuse;
    vec3 specular=material.specular;

    if(hasTexture){
        ambient*=texture(texMat.diffuse, TexCoords).rgb;
        diffuse*=texture(texMat.diffuse, TexCoords).rgb;
        specular*=texture(texMat.specular, TexCoords).rgb;
    }

    fragResult=ambient+diffuse+specular;

    FragColor=vec4(fragResult,1.f);
}