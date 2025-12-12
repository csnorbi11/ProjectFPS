#include "DirectionalLight.hpp"

#include "../graphics/ShaderProgram.hpp"


DirectionalLight::DirectionalLight(const DirectionalLightParams& param,
        const LightParams& lightParams)
        :
    Light(lightParams),
    direction(param.direction)
{}

void DirectionalLight::apply(ShaderProgram *program) {
    program->setVec3("dirLight.direction", direction);
    program->setVec3("dirLight.color", color);
    program->setFloat("dirLight.intensity", intensity);
}

void DirectionalLight::setDirection(const glm::vec3 &direction) {
    this->direction = direction;
}



const glm::vec3& DirectionalLight::getDirection() const {
    return direction;
}
