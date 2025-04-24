#include "headers/Light.hpp"

#include "headers/ShaderProgram.hpp"

Light::Light(const LightParams& params)
    :
    ambient(params.ambient),
    diffuse(params.diffuse),
    specular(params.specular),
    intensity(params.intensity)
{}

Light::~Light()=default;

void Light::update(ShaderProgram* program) {
    program->setVec3("dirLight.ambient", ambient);
    program->setVec3("dirLight.diffuse", diffuse);
    program->setVec3("dirLight.specular", specular);
    program->setFloat("dirLight.intensity", intensity);
}
