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
    quadratic(params.quadratic),
    index(params.index)
{}

PointLight::~PointLight() =default;

void PointLight::apply(ShaderProgram *program) {
    program->setFloat("pointLights["+std::to_string(index)+"].constant",constant);
    program->setFloat("pointLights["+std::to_string(index)+"].linear",linear);
    program->setFloat("pointLights["+std::to_string(index)+"].quadratic",quadratic);
    program->setVec3("pointLights["+std::to_string(index)+"].position",position);
    program->setVec3("pointLights["+std::to_string(index)+"].ambient", ambient);
    program->setVec3("pointLights["+std::to_string(index)+"].diffuse", diffuse);
    program->setVec3("pointLights["+std::to_string(index)+"].specular", specular);
}
