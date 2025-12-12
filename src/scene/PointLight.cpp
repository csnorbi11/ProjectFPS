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
        MaterialParam{ ambient,diffuse,specular,1.f }, MaterialTextureParam{}
    );
    updateBulbMaterial();
}

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

void PointLight::update(float deltaTime)
{


}

void PointLight::setColor(glm::vec3 color)
{
    ambient = color;
    diffuse = color;
    specular = color;

    updateBulbMaterial();
}

void PointLight::updateBulbMaterial()
{
    bulbMaterial->changeAmbientColor(ambient);
    bulbMaterial->changeAmbientColor(diffuse);
    bulbMaterial->changeAmbientColor(specular);
    overrideMaterials.insert_or_assign(model->getMeshes().begin()->second->getName(), bulbMaterial.get());
}
