#include "Shader.hpp"

#include <fstream>
#include <sstream>
#include <stdexcept>

Shader::Shader(const char *path, GLenum shaderType)
    : shaderType(shaderType) {
    std::string shaderCode;
    std::ifstream shaderFile;

    shaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        shaderFile.open(path);
        std::stringstream shaderStream;

        shaderStream << shaderFile.rdbuf();
        shaderFile.close();

        shaderCode = shaderStream.str();
    } catch (std::ifstream::failure &e) {
        throw std::runtime_error("Failed to read file");
    }
    const char *shaderSource = shaderCode.c_str();

    shader = glCreateShader(shaderType);
    glShaderSource(shader, 1, &shaderSource, nullptr);
    glCompileShader(shader);

    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        throw std::runtime_error("Failed to compile shader: " + std::to_string(*infoLog) + "\n" + path);
    }
}

Shader::~Shader() noexcept {
    glDeleteShader(shader);
}

GLenum Shader::getShaderType() const {
    return shaderType;
}

const GLuint &Shader::getShader() const {
    return shader;
}
