#include "headers/Light.hpp"

Light::Light(const LightParams& params)
    :
    ambient(params.ambient),
    diffuse(params.diffuse),
    specular(params.specular),
    intensity(params.intensity)
{}

Light::~Light()=default;
