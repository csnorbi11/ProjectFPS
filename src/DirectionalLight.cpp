#include "headers/DirectionalLight.hpp"

#include "headers/ShaderProgram.hpp"


DirectionalLight::DirectionalLight(const DirectionalLightParams& param,
        const LightParams& lightParams)
        :
    Light(lightParams),
    direction(param.direction),
    intensity(param.intensity)
{}

DirectionalLight::~DirectionalLight()=default;

void DirectionalLight::update(ShaderProgram *program) {
    program->setVec3("dirLight.direction", direction);
    program->setVec3("dirLight.ambient", ambient);
    program->setVec3("dirLight.diffuse", diffuse);
    program->setVec3("dirLight.specular", specular);
    program->setFloat("dirLight.intensity", intensity);
}

void DirectionalLight::setDirection(const glm::vec3 &direction) {
    this->direction = direction;
}

void DirectionalLight::setIntensity(float intensity) {
    if (intensity>0.f&&intensity<=1.f) {
        this->intensity = intensity;
    }else if (intensity<=0.f) {
        this->intensity = 0.1f;
    }
}

float DirectionalLight::getIntensity() const {
    return intensity;
}

const glm::vec3& DirectionalLight::getDirection() const {
    return direction;
}
