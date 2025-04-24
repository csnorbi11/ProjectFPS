#ifndef POINTLIGHT_HPP
#define POINTLIGHT_HPP
#include "GameObject.hpp"
#include "Light.hpp"

class PointLight final : public Light, public GameObject {
public:
    PointLight();
    ~PointLight() override;

    void update(ShaderProgram* program) override;

private:
    float constant;
    float linear;
    float quadratic;
};


#endif //POINTLIGHT_HPP
