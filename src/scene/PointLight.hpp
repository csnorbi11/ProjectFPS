#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP

#include "GameObject.hpp"
#include "Light.hpp"

struct PointLightParams {
    uint32_t index=0;
    float constant = 1.0f;
    float linear = 0.35f;
    float quadratic = 0.44f;
};

class PointLight final : public Light, public GameObject {
public:
    explicit PointLight(const PointLightParams& params=PointLightParams(),
        const LightParams& lightParams=LightParams(),
        const GameObjectParams& gameObjectParams={nullptr,
        glm::vec3(0.f),glm::vec3(0.f)});
    ~PointLight() override;

    void apply(ShaderProgram* program) override;
    void update(float deltaTime) override;

private:
    float constant;
    float linear;
    float quadratic;

    uint32_t index;
    
};


#endif //POINTLIGHT_HPP
