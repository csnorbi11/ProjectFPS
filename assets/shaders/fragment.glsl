#version 430
out vec4 FragColor;

in vec3 Normal;
in vec3 Color;
in vec2 TexCoords;

uniform bool hasTexture;

uniform sampler2D texture_diffuse1;

void main()
{
    if(hasTexture)
        FragColor = texture(texture_diffuse1, TexCoords);
    else
        FragColor=vec4(Color,1.0f);
}