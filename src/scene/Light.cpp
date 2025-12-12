#include "Light.hpp"
#include <memory>


#include "../graphics/ShaderProgram.hpp"

Light::Light(const LightParams& params)
{
    setColorAndIntensity(params.color, params.intensity);
}

Light::~Light()=default;

void Light::setColor(glm::vec3 color)
{
    if (color.length() > 1) {
        this->color = glm::normalize(color);
    }
    else if (color.length() < 0) {
        this->color = glm::vec3{ 1.f };
    }
    else {
        this->color = color;
    }
}

void Light::setIntensity(float intensity)
{
    if(intensity>0)
        this->intensity = intensity;
}

void Light::setColorAndIntensity(glm::vec3 color, float intensity)
{
    setColor(color);
    setIntensity(intensity);
}

glm::vec3 Light::getColor()
{
    return color;
}

float Light::getIntensity()
{
    return intensity;
}