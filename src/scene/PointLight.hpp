#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "GameObject.hpp"
#include "Light.hpp"
#include "graphics/Material.hpp"

struct PointLightParams {
    size_t index;
    float constant = 1.0f;
    float linear = 0.35f;
    float quadratic = 0.44f;
};

class PointLight final : public Light, public GameObject {
public:
    explicit PointLight(AssetManager& assetManager, const PointLightParams& params=PointLightParams(),
        const LightParams& lightParams=LightParams(),
        const GameObjectParams& gameObjectParams = { nullptr,
        glm::vec3(0.f),glm::vec3(0.f)});
    ~PointLight() override;

    void apply(ShaderProgram* program) override;
    void update(float deltaTime) override;

    virtual void setColor(glm::vec3 color) override;
    virtual void setIntensity(float intensity) override;
    virtual void setColorAndIntensity(glm::vec3 color, float intensity) override;

private:
    void updateBulbMaterial();


    float constant;
    float linear;
    float quadratic;

    size_t index;

    std::unique_ptr<Material> bulbMaterial;
    
};


#endif //POINTLIGHT_HPP
