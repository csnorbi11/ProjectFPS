#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP
#include "Light.hpp"

struct DirectionalLightParams {
    glm::vec3 direction=glm::vec3(0.f,-1.f,0.f);
    float intensity=1.f;
};

class DirectionalLight : public Light {
public:
    explicit DirectionalLight(const DirectionalLightParams& params=DirectionalLightParams(),
        const LightParams& lightParams=LightParams());
    ~DirectionalLight() override;

    void update(ShaderProgram* program) override;

    void setDirection(const glm::vec3& direction);
    void setIntensity(float intensity);
    const glm::vec3& getDirection() const;
    float getIntensity() const;


private:
    glm::vec3 direction;
    float intensity;
};


#endif //DIRECTIONALLIGHT_HPP
