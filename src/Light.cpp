#include "headers/Light.hpp"

Light::Light(glm::vec3 ambient, glm::vec3 diffuse, glm::vec3 specular,float intensity)
    :
    ambient(ambient),
    diffuse(diffuse),
    specular(specular),
    intensity(intensity)
{}

Light::~Light()=default;
