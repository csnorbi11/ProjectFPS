#include "headers/DirectionalLight.hpp"

#include "headers/ShaderProgram.hpp"


DirectionalLight::DirectionalLight(glm::vec3 direction,
        const LightParams& lightParams)
        :
    Light(lightParams),
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
