#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP
#include "Light.hpp"


class DirectionalLight : public Light {
public:
    DirectionalLight(glm::vec3 direction=glm::vec3(0.f,-1.f,0.f),
        const LightParams& lightParams=LightParams());


    ~DirectionalLight() override;

    void update(ShaderProgram* program) override;


private:
    glm::vec3 direction;
};


#endif //DIRECTIONALLIGHT_HPP
