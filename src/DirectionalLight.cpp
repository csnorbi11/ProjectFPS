#include "headers/DirectionalLight.hpp"

#include "headers/ShaderProgram.hpp"

DirectionalLight::DirectionalLight()
        :
    direction(glm::vec3(0.f,-1.f,0.f))
{}

DirectionalLight::DirectionalLight(glm::vec3 direction,glm::vec3 ambient,
    glm::vec3 diffuse,glm::vec3 specular,float intensity)
        :
    Light(ambient, diffuse, specular,intensity),
    direction(direction)
{}

DirectionalLight::~DirectionalLight()=default;

void DirectionalLight::update(ShaderProgram *program) {
    program->setVec3("dirLight.direction", direction);
    program->setVec3("dirLight.ambient", ambient);
    program->setVec3("dirLight.diffuse", diffuse);
    program->setVec3("dirLight.specular", specular);
    program->setFloat("dirLight.intensity", intensity);
}
