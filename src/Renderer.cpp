#include "headers/Renderer.hpp"

#include <iostream>

#include "headers/Camera.hpp"
#include "headers/DirectionalLight.hpp"
#include "headers/GameObject.hpp"
#include "headers/Map.hpp"
#include "headers/Model.hpp"
#include "headers/PointLight.hpp"
#include "headers/Scene.hpp"
#include "headers/Shader.hpp"
#include "headers/ShaderProgram.hpp"
#include "headers/WindowHandler.hpp"

Renderer::Renderer()=default;

Renderer::~Renderer() {
    currentScene=nullptr;
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

void Renderer::applyDirectionalLight() {
    if (currentScene->directionalLight==nullptr) return;
    currentScene->directionalLight->apply(shaderPrograms["basic"].get());
}

void Renderer::applyPointLights() {
    shaderPrograms["basic"]->setInt("activePointLights",static_cast<int>(currentScene->pointLights.size()));
    for (auto& light:currentScene->pointLights) {
        light->apply(shaderPrograms["basic"].get());
    }
}

void Renderer::drawPointLights() {
    for (auto &light:currentScene->pointLights) {
        if (models.count(light->getModelPath())==0) {
            loadModel(light->getModelPath(),"pointLight");
        }

        Model *model=models[light->getModelPath()].get();
        if (activeShaderProgram != model->getShaderProgName()) {
            activeShaderProgram = model->getShaderProgName();
            shaderPrograms[activeShaderProgram]->use();
            applyDirectionalLight();
            applyPointLights();
        }


        glm::mat4 transformMatrix(1.f);
        transformMatrix = glm::translate(glm::mat4(1.0f), light->position);
        transformMatrix = glm::rotate(transformMatrix, light->rotation.x, glm::vec3(0.0f,1.0f,0.0f));
        transformMatrix = glm::rotate(transformMatrix, light->rotation.y, glm::vec3(1.0f,0.0f,0.0f));
        transformMatrix = glm::rotate(transformMatrix, light->rotation.z, glm::vec3(0.0f,0.0f,1.0f));
        shaderPrograms[activeShaderProgram]->setMat4("model",transformMatrix);
        viewProjection();
        shaderPrograms[activeShaderProgram]->setVec3("color",light->getDiffuse());


        model->getMeshes()[0]->bindVAO();
        glDrawElements(GL_TRIANGLES, static_cast<int>(model->getMeshes()[0]->getIndices().size()), GL_UNSIGNED_INT, 0);
        model->getMeshes()[0]->unbindVAO();
    }
}

void Renderer::drawScene() {
    if (currentScene==nullptr) return;
    drawMap();
    drawPointLights();
    drawGameObjects();
}

void Renderer::viewProjection() {
    shaderPrograms[activeShaderProgram]->setMat4("projection",
                                                 glm::perspective(glm::radians(90.0f),WindowHandler::getAspectRatio(),0.01f,100.0f));
    shaderPrograms[activeShaderProgram]->setMat4("view",currentScene->camera->getViewMatrix());
}

void Renderer::drawGameObjects() {
    for (auto &gameObject : currentScene->gameObjects) {
    if (models.count(gameObject->getModelPath()) == 0) {
        loadModel(gameObject->getModelPath(), "basic");
    }

    Model *model = models[gameObject->getModelPath()].get();
    if (activeShaderProgram != model->getShaderProgName()) {
        activeShaderProgram = model->getShaderProgName();
        shaderPrograms[activeShaderProgram]->use();
        applyDirectionalLight();
        applyPointLights();
    }
    viewProjection();
    for (const auto &mesh : model->getMeshes()) {
        glm::mat4 transformMatrix(1.f);
        transformMatrix = glm::translate(glm::mat4(1.0f), gameObject->position);
        transformMatrix = glm::rotate(transformMatrix, gameObject->rotation.x, glm::vec3(0.0f,1.0f,0.0f));
        transformMatrix = glm::rotate(transformMatrix, gameObject->rotation.y, glm::vec3(1.0f,0.0f,0.0f));
        transformMatrix = glm::rotate(transformMatrix, gameObject->rotation.z, glm::vec3(0.0f,0.0f,1.0f));
        shaderPrograms[activeShaderProgram]->setVec3("viewPos", currentScene->camera->position);
        shaderPrograms[activeShaderProgram]->setMat4("model",transformMatrix);
        shaderPrograms[activeShaderProgram]->setBool("hasTexture",!(mesh->getTextures().empty()));
         for (int i=0;i<mesh->getTextures().size();i++) {
             glActiveTexture(GL_TEXTURE0 + i);
             std::string name = mesh->getTextures()[i].type;
             if(name == "texture_diffuse") {
                 shaderPrograms[activeShaderProgram]->setInt("material.diffuse",i);
             }
             else if(name == "texture_specular") {
                 shaderPrograms[activeShaderProgram]->setInt("material.specular",i);
             }


             glBindTexture(GL_TEXTURE_2D, mesh->getTextures()[i].id);
         }
        mesh->bindVAO();
        glDrawElements(GL_TRIANGLES, static_cast<int>(mesh->getIndices().size()), GL_UNSIGNED_INT, 0);
        mesh->unbindVAO();
        glActiveTexture(GL_TEXTURE0);
    }
    }



}
void Renderer::drawMap() {
    if (currentScene->loadedMap == nullptr) return;
    if (activeShaderProgram != currentScene->loadedMap->getShaderProgName()) {
        activeShaderProgram = currentScene->loadedMap->getShaderProgName();
        shaderPrograms[activeShaderProgram]->use();

    }
    applyDirectionalLight();
    applyPointLights();
    viewProjection();
    shaderPrograms[activeShaderProgram]->setMat4("model",glm::mat4(1.0f));
    shaderPrograms[activeShaderProgram]->setVec3("material.ambient", {1.0f, 0.5f, 0.31f});
    shaderPrograms[activeShaderProgram]->setVec3("material.diffuse", {1.0f, 0.5f, 0.31f});
    shaderPrograms[activeShaderProgram]->setVec3("material.specular", {0.1f, 0.1f, 0.1f});
    shaderPrograms[activeShaderProgram]->setFloat("material.shininess", 32.0f);
    shaderPrograms[activeShaderProgram]->setVec3("viewPos", currentScene->camera->position);
    for (const auto &mesh : currentScene->loadedMap->getMeshes()) {
        shaderPrograms[activeShaderProgram]->setBool("hasTexture",!(mesh->getTextures().empty()));
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


void Renderer::setActiveScene(Scene* scene) {
    currentScene=scene;
}
