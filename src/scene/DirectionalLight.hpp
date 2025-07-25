#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP

#include "Light.hpp"

struct DirectionalLightParams {
    glm::vec3 direction=glm::vec3(0.f,-1.f,0.f);
    float intensity=0.5f;
};

class DirectionalLight final : public Light {
public:
    explicit DirectionalLight(const DirectionalLightParams& params=DirectionalLightParams(),
        const LightParams& lightParams=LightParams());
    ~DirectionalLight() override = default;;

    void apply(ShaderProgram* program) override;

    void setDirection(const glm::vec3& direction);
    void setIntensity(float intensity);
    const glm::vec3& getDirection() const;
    float getIntensity() const;


private:
    glm::vec3 direction;
    float intensity;
};


#endif //DIRECTIONALLIGHT_HPP
