#include "headers/Renderer.hpp"

#include <iostream>
#include <map>

#include "headers/Camera.hpp"
#include "headers/GameObject.hpp"
#include "headers/Map.hpp"
#include "headers/Model.hpp"
#include "headers/Shader.hpp"
#include "headers/ShaderProgram.hpp"
#include "headers/WindowHandler.hpp"

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
        glm::perspective(glm::radians(90.0f),WindowHandler::getAspectRatio(),0.01f,100.0f));
    shaderPrograms[activeShaderProgram]->setMat4("view",camera->getViewMatrix());
    for (const auto &mesh : model->getMeshes()) {
        glm::mat4 transformMatrix(1.f);
        transformMatrix = glm::translate(glm::mat4(1.0f), gameObject.position);
        transformMatrix = glm::rotate(transformMatrix, gameObject.rotation.x, glm::vec3(0.0f,1.0f,0.0f));
        transformMatrix = glm::rotate(transformMatrix, gameObject.rotation.y, glm::vec3(1.0f,0.0f,0.0f));
        transformMatrix = glm::rotate(transformMatrix, gameObject.rotation.z, glm::vec3(0.0f,0.0f,1.0f));
        shaderPrograms[activeShaderProgram]->setMat4("model",transformMatrix);

        // bind appropriate textures
        uint32_t diffuseNr  = 1;
        uint32_t specularNr = 1;
        uint32_t normalNr   = 1;
        uint32_t heightNr   = 1;
         for (int i=0;i<mesh->getTextures().size();i++) {
             glActiveTexture(GL_TEXTURE0 + i);
             std::string number;
             std::string name = mesh->getTextures()[i].type;
             if(name == "texture_diffuse")
                 number = std::to_string(diffuseNr++);
             else if(name == "texture_specular")
                 number = std::to_string(specularNr++); // transfer unsigned int to string
             else if(name == "texture_normal")
                 number = std::to_string(normalNr++); // transfer unsigned int to string
             else if(name == "texture_height")
                 number = std::to_string(heightNr++);
             shaderPrograms[activeShaderProgram]->setInt(name + number,i);
             glBindTexture(GL_TEXTURE_2D, mesh->getTextures()[i].id);
         }
        mesh->bindVAO();
        glDrawElements(GL_TRIANGLES, static_cast<int>(mesh->getIndices().size()), GL_UNSIGNED_INT, 0);
        mesh->unbindVAO();
        glActiveTexture(GL_TEXTURE0);
    }


}

void Renderer::drawMap() {
    if (currentMap == nullptr) return;
    if (activeShaderProgram != currentMap->getShaderProgName()) {
        activeShaderProgram = currentMap->getShaderProgName();
        shaderPrograms[activeShaderProgram]->use();
    }
    shaderPrograms[activeShaderProgram]->setMat4("projection",
        glm::perspective(glm::radians(90.0f),WindowHandler::getAspectRatio(),0.01f,100.0f));
    shaderPrograms[activeShaderProgram]->setMat4("view",camera->getViewMatrix());
    shaderPrograms[activeShaderProgram]->setMat4("model",glm::mat4(1.0f));
    for (const auto &mesh : currentMap->getMeshes()) {
        // bind appropriate textures
        uint32_t diffuseNr  = 1;
        uint32_t specularNr = 1;
        uint32_t normalNr   = 1;
        uint32_t heightNr   = 1;
        for (int i=0;i<mesh->getTextures().size();i++) {
            glActiveTexture(GL_TEXTURE0 + i);
            std::string number;
            std::string name = mesh->getTextures()[i].type;
            if(name == "texture_diffuse")
                number = std::to_string(diffuseNr++);
            else if(name == "texture_specular")
                number = std::to_string(specularNr++); // transfer unsigned int to string
            else if(name == "texture_normal")
                number = std::to_string(normalNr++); // transfer unsigned int to string
            else if(name == "texture_height")
                number = std::to_string(heightNr++);
            shaderPrograms[activeShaderProgram]->setInt(name + number,i);
            glBindTexture(GL_TEXTURE_2D, mesh->getTextures()[i].id);
        }
        mesh->bindVAO();
        glDrawElements(GL_TRIANGLES, static_cast<int>(mesh->getIndices().size()), GL_UNSIGNED_INT, 0);
        mesh->unbindVAO();
        glActiveTexture(GL_TEXTURE0);
    }
}

void Renderer::update() {
    if (WindowHandler::toggleKey(Input::Key::O)) {
        debugMode=!debugMode;
    }
    glPolygonMode(GL_FRONT_AND_BACK, debugMode ? GL_LINE : GL_FILL);
}

void Renderer::setActiveCamera(Camera* camera) {
    this->camera = camera;
}

void Renderer::setActiveMap(Map *map) {
    currentMap=map;
}
