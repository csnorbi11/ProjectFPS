#include "headers/Renderer.hpp"

#include "headers/GameObject.hpp"
#include "headers/Model.hpp"
#include "headers/Shader.hpp"
#include "headers/ShaderProgram.hpp"

Renderer::Renderer() {
}

Renderer::~Renderer() {
    models.clear();
    shaderPrograms.clear();
    shaders.clear();
}


void Renderer::loadModel(const std::string &path, const std::string &shaderProgName) {
    models.emplace(path, std::make_unique<Model>(shaderProgName));
}

void Renderer::loadShader(const std::string &path, const GLenum shaderType) {
    shaders.emplace(path, std::make_unique<Shader>(path.c_str(), shaderType));
}

void Renderer::createShaderProgram(const std::string &name,
                                   const std::string &vertexShader, const std::string &fragmentShader) {
    if (shaders.count(vertexShader) == 0) {
        loadShader(vertexShader,GL_VERTEX_SHADER);
    }
    if (shaders.count(fragmentShader) == 0) {
        loadShader(fragmentShader,GL_FRAGMENT_SHADER);
    }
    shaderPrograms.emplace(name, std::make_unique<ShaderProgram>(*shaders[vertexShader],
                                                                 *shaders[fragmentShader]));
}

void Renderer::draw(const GameObject &gameObject) {
    if (models.count(gameObject.getModelPath()) == 0) {
        loadModel(gameObject.getModelPath(), "basic");
    }

    Model *model = models[gameObject.getModelPath()].get();
    if (activeShaderProgram != model->getShaderProgName()) {
        activeShaderProgram = model->getShaderProgName();
        shaderPrograms[activeShaderProgram]->use();
    }
    model->draw();
}
