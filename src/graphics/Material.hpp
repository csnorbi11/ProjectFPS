#ifndef MATERIAL_HPP
#define MATERIAL_HPP

#include <glm/vec3.hpp>

#include "ShaderProgram.hpp"


struct Texture {
    uint32_t id;
    std::string type;
    std::string path;
};

class Material {



private:
    glm::vec3 ambient{};

	ShaderProgram* program = nullptr;
};



#endif // !MATERIAL_HPP
