#include "headers/ShaderProgram.hpp"

#include <stdexcept>

ShaderProgram::ShaderProgram(Shader vertexShader, Shader fragmentShader) {
    if (vertexShader.getShaderType() != GL_VERTEX_SHADER || fragmentShader.getShaderType() != GL_FRAGMENT_SHADER) {
        throw std::runtime_error("Failed to load vertex shader");
    }

    program = glCreateProgram();
    glAttachShader(program, vertexShader.getShader());
    glAttachShader(program, fragmentShader.getShader());
    glLinkProgram(program);

    int success;
    char infoLog[512];
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        glGetProgramInfoLog(program, 512, NULL, infoLog);
        throw std::runtime_error("Failed to link shader program: " + std::to_string(*infoLog));
    }
}

ShaderProgram::~ShaderProgram() {
    glDeleteProgram(program);
}

void ShaderProgram::use() const {
    glUseProgram(program);
}

void ShaderProgram::setBool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(program, name.c_str()), (int) value);
}

void ShaderProgram::setInt(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void ShaderProgram::setFloat(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(program, name.c_str()), value);
}

void ShaderProgram::setVec3(const std::string &name, glm::vec3 value) const {
    glUniform3fv(glGetUniformLocation(program, name.c_str()), 1, glm::value_ptr(value));
}

void ShaderProgram::setMat4(const std::string &name, glm::mat4 value) const {
    glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1,GL_FALSE, glm::value_ptr(value));
}
