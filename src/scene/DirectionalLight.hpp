#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "Light.hpp"

struct DirectionalLightParams {
    glm::vec3 direction=glm::vec3(0.f,-1.f,0.f);
};

class DirectionalLight final : public Light {
public:
    explicit DirectionalLight(const DirectionalLightParams& params=DirectionalLightParams(),
        const LightParams& lightParams=LightParams());
    ~DirectionalLight() override = default;

    void apply(ShaderProgram* program) override;

    void setDirection(const glm::vec3& direction);
    const glm::vec3& getDirection() const;


private:
    glm::vec3 direction;
};


#endif //DIRECTIONALLIGHT_HPP
