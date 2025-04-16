#include "headers/Renderer.hpp"

#include <iostream>

#include "headers/Camera.hpp"
#include "headers/GameObject.hpp"
#include "headers/Model.hpp"
#include "headers/Shader.hpp"
#include "headers/ShaderProgram.hpp"

Renderer::Renderer() = default;

Renderer::~Renderer() {
    models.clear();
    shaderPrograms.clear();
    shaders.clear();
}


void Renderer::loadModel(const std::string &path, const std::string &shaderProgName) {
    models.emplace(path, std::make_unique<Model>(path.c_str(), shaderProgName));
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
    shaderPrograms[activeShaderProgram]->setMat4("projection",
        glm::perspective(glm::radians(90.0f),(float)800/(float)600,0.01f,100.0f));
    shaderPrograms[activeShaderProgram]->setMat4("view",camera->getViewMatrix());
    for (const auto &mesh : model->getMeshes()) {
        glm::mat4 transformMatrix(1.f);
        transformMatrix = glm::translate(glm::mat4(1.0f), gameObject.position);
        transformMatrix = glm::rotate(transformMatrix, gameObject.rotation.x, glm::vec3(0.0f,1.0f,0.0f));
        transformMatrix = glm::rotate(transformMatrix, gameObject.rotation.y, glm::vec3(1.0f,0.0f,0.0f));
        transformMatrix = glm::rotate(transformMatrix, gameObject.rotation.z, glm::vec3(0.0f,0.0f,1.0f));
        shaderPrograms[activeShaderProgram]->setMat4("model",transformMatrix);

        uint32_t diffuseNr=1;
        uint32_t specularNr=1;
         for (int i=0;i<mesh->getTextures().size();i++) {
             glActiveTexture(GL_TEXTURE0 + i);
             std::string number;
             std::string name = mesh->getTextures()[i].type;
             if (name == "texture_diffuse") {
                 number = std::to_string(diffuseNr++);
             } else if (name == "texture_specular") {
                 number = std::to_string(specularNr++);
             }
             shaderPrograms[activeShaderProgram]->setInt(name + number,i);
         }
        mesh->bindVAO();
        glDrawElements(GL_TRIANGLES, static_cast<int>(mesh->getIndices().size()), GL_UNSIGNED_INT, 0);
        mesh->unbindVAO();
    }


}

void Renderer::setActiveCamera(Camera* camera) {
    this->camera = camera;
}
