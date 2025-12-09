#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glm/vec3.hpp>

#include "ShaderProgram.hpp"


struct Texture {
    uint32_t id;
    std::string type;
    std::string path;
};

struct MaterialParam {
    glm::vec3 ambient{ 0.1f };
    glm::vec3 diffuse{ 1.f };
    glm::vec3 specular{ 0.5f };
    float shininess = 32.f;
};

struct MaterialTextureParam {
    Texture* diffuseMap = nullptr;
    Texture* specularMap = nullptr;
    Texture* normalMap = nullptr;
};

class Material {
public:
    Material() = delete;
    Material(ShaderProgram* program, const MaterialParam& matParam,
        const MaterialTextureParam& matTexture);
    ~Material();

    void apply() const;

private:
    glm::vec3 ambient{0.1f};
    glm::vec3 diffuse{1.f};
    glm::vec3 specular{0.5f};
    float shininess = 32.f;

    bool hasTexture = false;
    Texture* diffuseMap = nullptr;
    Texture* specularMap = nullptr;
    Texture* normalMap = nullptr;

    const uint32_t diffuseMapID = 0;
    const uint32_t specularMapID = 1;
    const uint32_t normalMapID = 2;

	ShaderProgram* program = nullptr;
};



#endif // !MATERIAL_HPP
