#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <glm/vec3.hpp>

class ShaderProgram;

struct LightParams {
    glm::vec3 ambient{0.4f};
    glm::vec3 diffuse{1.f};
    glm::vec3 specular{1.f};
    float intensity=1.f;
};

class Light {
public:
    Light(const LightParams& params);
    virtual ~Light()=0;

    virtual void update(ShaderProgram* program);

public:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
    float intensity;
};


#endif //LIGHT_HPP
