#ifndef SHADER_HPP
#define SHADER_HPP

#include <glad/glad.h>

class Shader {
public:
    Shader(const char *path, GLenum shaderType);
    ~Shader() noexcept;

    GLenum getShaderType() const;
    const GLuint &getShader() const;

private:
    GLuint shader;
    GLenum shaderType;
};


#endif //SHADER_HPP
