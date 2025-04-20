#ifndef DIRECTIONALLIGHT_HPP
#define DIRECTIONALLIGHT_HPP
#include "Light.hpp"


class DirectionalLight : public Light {
public:
    DirectionalLight();
    DirectionalLight(glm::vec3 direction=glm::vec3(0.f,-1.f,0.f),
        glm::vec3 ambient=glm::vec3(0.4f),
        glm::vec3 diffuse=glm::vec3(1.0f),
        glm::vec3 specular=glm::vec3(1.0f),float intensity=1.f);


    ~DirectionalLight() override;

    void update(ShaderProgram* program) override;


private:
    glm::vec3 direction;
};


#endif //DIRECTIONALLIGHT_HPP
