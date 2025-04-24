#include "headers/PointLight.hpp"

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
}
