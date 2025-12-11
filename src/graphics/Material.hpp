#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glm/vec3.hpp>
#include <cstdint>

#include "ShaderProgram.hpp"
#include "Texture.hpp"



struct MaterialParam {
    glm::vec3 ambient{ 0.3f };
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
    Material(const std::string& name, ShaderProgram* program,
        const MaterialParam& matParam, const MaterialTextureParam& matTexture);
    ~Material();

    void apply() const;

    const std::string& getName();
    void changeDiffuseTexture(Texture* newTexture);
    void changeSpecularTexture(Texture* newTexture);
    ShaderProgram* getProgram();

private:
    const std::string name;

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
