#ifndef SHADERPROGRAM_HPP
#define SHADERPROGRAM_HPP

#include <glm/gtc/type_ptr.hpp>
#include <string>

#include "Shader.hpp"

class ShaderProgram {
public:
    ShaderProgram(Shader vertexShader, Shader fragmentShader);
    ~ShaderProgram();

    void use() const;

    void setBool(const std::string &name, bool value) const;
    void setInt(const std::string &name, int value) const;
    void setFloat(const std::string &name, float value) const;
    void setVec3(const std::string &name, glm::vec3 value) const;
    void setMat4(const std::string &name, glm::mat4 value) const;

private:
    uint32_t program;
};

#endif //SHADERPROGRAM_HPP
