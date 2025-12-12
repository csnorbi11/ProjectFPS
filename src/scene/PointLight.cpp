#include "PointLight.hpp"

#include <GLFW/glfw3.h>
#include "../graphics/ShaderProgram.hpp"

PointLight::PointLight(AssetManager& assetManager, const PointLightParams& params,
                       const LightParams& lightParams,
                       const GameObjectParams& gameObjectParams)
                :
    Light(lightParams),
    GameObject(gameObjectParams),
    constant(params.constant),
    linear(params.linear),
    quadratic(params.quadratic),
    index(params.index)
{
    std::string name{ "light" };
    bulbMaterial = std::make_unique<Material>(
        std::move(name), assetManager.getShaderPrograms()["unlit"].get(),
        MaterialParam{ color,color,color,1.f }, MaterialTextureParam{}
    );
    updateBulbMaterial();
}

PointLight::~PointLight() =default;

void PointLight::apply(ShaderProgram *program) {
    program->setFloat("pointLights["+std::to_string(index)+"].constant",constant);
    program->setFloat("pointLights["+std::to_string(index)+"].linear",linear);
    program->setFloat("pointLights["+std::to_string(index)+"].quadratic",quadratic);
    program->setVec3("pointLights["+std::to_string(index)+"].position",position);
    program->setVec3("pointLights["+std::to_string(index)+"].color", color);
    program->setFloat("pointLights["+std::to_string(index)+"].intensity", intensity);
}

void PointLight::update(float deltaTime)
{


}

void PointLight::setColor(glm::vec3 color)
{
    Light::setColor(color);
    updateBulbMaterial();
}

void PointLight::setIntensity(float intensity)
{
    Light::setIntensity(intensity);
    updateBulbMaterial();
}

void PointLight::setColorAndIntensity(glm::vec3 color, float intensity)
{
    Light::setColorAndIntensity(color, intensity);
    updateBulbMaterial();
}



void PointLight::updateBulbMaterial()
{
    bulbMaterial->changeAmbientColor(color/intensity);
    bulbMaterial->changeDiffuseColor(color/intensity);
    bulbMaterial->changeSpecularColor(color/intensity);
    overrideMaterials.insert_or_assign(model->getMeshes().begin()->second->getName(), bulbMaterial.get());
}
