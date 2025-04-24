#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <glm/vec3.hpp>

class ShaderProgram;

struct LightParams {
    glm::vec3 ambient{0.4f};
    glm::vec3 diffuse{1.f};
    glm::vec3 specular{1.f};
};

class Light {
public:
    explicit Light(const LightParams& params);
    virtual ~Light()=0;

    virtual void update(ShaderProgram* program)=0;

    void setAmbient(const glm::vec3& ambient);
    void setDiffuse(const glm::vec3& diffuse);
    void setSpecular(const glm::vec3& specular);
    void setOverallColor(const glm::vec3& color, float ambientFactor=0.4f);
    const glm::vec3& getAmbient() const;
    const glm::vec3& getDiffuse() const;
    const glm::vec3& getSpecular() const;

protected:
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;
};


#endif //LIGHT_HPP
