#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <glm/vec3.hpp>

class Light {
public:
    Light();
    virtual ~Light()=0;

protected:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};

#endif //LIGHT_HPP
