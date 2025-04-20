#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <glm/vec3.hpp>

class ShaderProgram;

class Light {
public:
    explicit Light(glm::vec3 ambient=glm::vec3(0.4f),
        glm::vec3 diffuse=glm::vec3(1.0f),
        glm::vec3 specular=glm::vec3(1.0f),float intensity=1.f);
    virtual ~Light();

    virtual void update(ShaderProgram* program)=0;

protected:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float intensity;
};


#endif //LIGHT_HPP
