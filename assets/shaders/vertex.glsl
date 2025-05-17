#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aAmbient;
layout (location = 3) in vec3 aDiffuse;
layout (location = 4) in vec3 aSpecular;
layout (location = 5) in vec2 aTexCoords;

out vec3 Normal;
out vec3 Ambient;
out vec3 Diffuse;
out vec3 Specular;
out vec2 TexCoords;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    Normal = mat3(transpose(inverse(model))) * aNormal;
    Ambient = aAmbient;
    Diffuse = aDiffuse;
    Specular = aSpecular;
    TexCoords = aTexCoords;
    gl_Position = projection * view * model * vec4(aPos, 1.0);
    FragPos=vec3(model*vec4(aPos,1.f));
}