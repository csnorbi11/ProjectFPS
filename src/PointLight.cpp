#include "headers/PointLight.hpp"

#include "headers/ShaderProgram.hpp"

PointLight::PointLight(const PointLightParams& params,
                       const LightParams& lightParams,
                       const GameObjectParams& gameObjectParams)
                :
    Light(lightParams),
    GameObject(gameObjectParams),
    constant(params.constant),
    linear(params.linear),
    quadratic(params.quadratic)
{}

PointLight::~PointLight() =default;

void PointLight::update(ShaderProgram *program) {
    program->setFloat("pointLight.constant",constant);
    program->setFloat("pointLight.linear",linear);
    program->setFloat("pointLight.quadratic",quadratic);
    Light::update(program);
}
