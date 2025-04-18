#version 430
out vec4 FragColor;

in vec3 Normal;
in vec3 Color;
in vec2 TexCoords;
in vec3 FragPos;

uniform bool hasTexture;

uniform vec3 lightColor;
uniform vec3 lightPos;

uniform sampler2D texture_diffuse1;

void main()
{
    vec3 fragResult=vec3(0.f);


    float ambientStrength=0.1f;
    vec3 ambient=ambientStrength*lightColor;

    vec3 normal=normalize(Normal);
    vec3 lightDir=normalize(lightPos-FragPos);
    float dif=max(dot(normal,lightDir),0);
    vec3 diffuse=dif*lightColor;

    fragResult=ambient+diffuse;
    if(hasTexture){
        fragResult*=texture(texture_diffuse1,TexCoords).rgb;
    }else{
        fragResult*=Color;
    }

    FragColor=vec4(fragResult,1.f);
}