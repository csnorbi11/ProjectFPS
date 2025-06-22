#include "Light.hpp"

#include "../graphics/ShaderProgram.hpp"

Light::Light(const LightParams& params)
    :
    ambient(params.ambient),
    diffuse(params.diffuse),
    specular(params.specular)
{}

Light::~Light()=default;


void Light::setAmbient(const glm::vec3 &ambient) {
    if (ambient.x>=0.f&&ambient.y>=0.f&&ambient.z>=0.f&&
        ambient.x<=1.f&&ambient.y<=1.f&&ambient.z<=1.f) {
        this->ambient = ambient;
    }
}

void Light::setDiffuse(const glm::vec3 &diffuse) {
    if (diffuse.x>=0.f&&diffuse.y>=0.f&&diffuse.z>=0.f&&
        diffuse.x<=1.f&&diffuse.y<=1.f&&diffuse.z<=1.f) {
        this->diffuse = diffuse;
        }
}

void Light::setSpecular(const glm::vec3 &specular) {
    if (specular.x>=0.f&&specular.y>=0.f&&specular.z>=0.f&&
        specular.x<=1.f&&specular.y<=1.f&&specular.z<=1.f) {
        this->specular = specular;
        }
}

void Light::setOverallColor(const glm::vec3 &color, float ambientFactor) {
    if (color.x>=0.f&&color.y>=0.f&&color.z>=0.f&&
        color.x<=1.f&&color.y<=1.f&&color.z<=1.f) {
        ambient = color;
        diffuse = color;
        specular = color;
        }
    if (ambientFactor<=0.f) {
        ambient*=0.1f;
    }
    else if (ambientFactor>1.f) {
        ambient*=1.f;
    }else {
        ambient*=ambientFactor;
    }
}

const glm::vec3 & Light::getAmbient() const {
    return ambient;
}

const glm::vec3 & Light::getDiffuse() const {
    return diffuse;
}

const glm::vec3 & Light::getSpecular() const {
    return specular;
}
