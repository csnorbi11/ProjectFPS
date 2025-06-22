#include "Renderer.hpp"

#include <iostream>

#include "../src/scene/Camera.hpp"
#include "../src/scene/DirectionalLight.hpp"
#include "../src/scene/GameObject.hpp"
#include "../src/scene/Map.hpp"
#include "Model.hpp"
#include "../src/scene/PointLight.hpp"
#include "../src/scene/Scene.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "../src/platform/GLFWInput.hpp"
#include "../src/platform/GLFWHandler.hpp"


Renderer::Renderer(GLFWHandler& glfwHandler)
    :
    glfwHandler(glfwHandler)
{}

Renderer::~Renderer() {
    activeScene=nullptr;
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
    activeScene->map->getDirectionalLight().apply(shaderPrograms["basic"].get());
}

void Renderer::applyPointLights() {
    shaderPrograms["basic"]->setInt(
        "activePointLights",static_cast<int>(activeScene->map->getPointLights().size()));
    for (auto& light:activeScene->map->getPointLights()) {
        light->apply(shaderPrograms["basic"].get());
    }
    for (auto& light : activeScene->dynamicLights) {
        light->apply(shaderPrograms["basic"].get());
    }
}

template<>
void Renderer::drawObjects<PointLight>(std::vector<std::unique_ptr<PointLight>>& objects) {
    for (const auto& object : objects) {



        if (!isModelLoaded(object->getModelPath())) {
            loadModel(object->getModelPath(), "pointLight");

        }
        if (!isShaderProgramActive("pointLight")) {
            activeShaderProgram = "pointLight";
            shaderPrograms[activeShaderProgram]->use();
        }
        shaderPrograms[activeShaderProgram]->setVec3("color", object->getDiffuse());
        drawObject<PointLight>(object.get());
    }
}

void Renderer::drawMap()
{

	drawObjects<StaticObject>(activeScene->map->getObjects());
	drawObjects<PointLight>(activeScene->map->getPointLights());
}

//void Renderer::drawPointLights() {
//    for (auto &light:activeScene->pointLights) {
//        if (models.count(light->getModelPath())==0) {
//            loadModel(light->getModelPath(),"pointLight");
//        }
//
//        Model *model=models[light->getModelPath()].get();
//        if (activeShaderProgram != model->getShaderProgName()) {
//            activeShaderProgram = model->getShaderProgName();
//            shaderPrograms[activeShaderProgram]->use();
//            applyDirectionalLight();
//            applyPointLights();
//        }
//
//
//        glm::mat4 transformMatrix(1.f);
//        transformMatrix *= static_cast<glm::mat4>(light->getQuaternion());
//        //transformMatrix = glm::translate(glm::mat4(1.0f), light->position);
//        shaderPrograms[activeShaderProgram]->setMat4("model",transformMatrix);
//        viewProjection();
//        shaderPrograms[activeShaderProgram]->setVec3("color",light->getDiffuse());
//
//
//        model->getMeshes()[0]->bindVAO();
//        glDrawElements(GL_TRIANGLES, static_cast<int>(model->getMeshes()[0]->getIndices().size()), GL_UNSIGNED_INT, 0);
//        model->getMeshes()[0]->unbindVAO();
//    }
//}

void Renderer::drawScene() {
    if (activeScene==nullptr) return;
	drawMap();
}

bool Renderer::isModelLoaded(const std::string& path) const
{
    return models.count(path) > 0;
}

bool Renderer::isShaderProgramActive(const std::string& programName) const
{
    return activeShaderProgram==programName;
}

void Renderer::viewProjection() {
    shaderPrograms[activeShaderProgram]->setMat4("projection",
                                                 glm::perspective(glm::radians(90.0f), glfwHandler.getAspectRatio(),0.01f,100.0f));
    shaderPrograms[activeShaderProgram]->setMat4("view",activeScene->camera->getViewMatrix());
}

//void Renderer::drawGameObjects() {
//    for (auto &gameObject : activeScene->gameObjects) {
//    if (models.count(gameObject->getModelPath()) == 0) {
//        loadModel(gameObject->getModelPath(), "basic");
//    }
//
//    Model *model = models[gameObject->getModelPath()].get();
//    if (activeShaderProgram != model->getShaderProgName()) {
//        activeShaderProgram = model->getShaderProgName();
//        shaderPrograms[activeShaderProgram]->use();
//        applyDirectionalLight();
//        applyPointLights();
//    }
//    viewProjection();
//    for (const auto &mesh : model->getMeshes()) {
//        glm::mat4 transformMatrix(1.f);
//        transformMatrix = glm::translate(glm::mat4(1.0f), gameObject->position);
//        transformMatrix *= static_cast<glm::mat4>(gameObject->getQuaternion());
//        shaderPrograms[activeShaderProgram]->setVec3("viewPos", activeScene->camera->position);
//        shaderPrograms[activeShaderProgram]->setMat4("model",transformMatrix);
//        shaderPrograms[activeShaderProgram]->setBool("hasTexture",!(mesh->getTextures().empty()));
//         for (int i=0;i<mesh->getTextures().size();i++) {
//             glActiveTexture(GL_TEXTURE0 + i);
//             std::string name = mesh->getTextures()[i].type;
//             if(name == "texture_diffuse") {
//                 shaderPrograms[activeShaderProgram]->setInt("material.diffuse",i);
//             }
//             else if(name == "texture_specular") {
//                 shaderPrograms[activeShaderProgram]->setInt("material.specular",i);
//             }
//
//
//             glBindTexture(GL_TEXTURE_2D, mesh->getTextures()[i].id);
//         }
//        mesh->bindVAO();
//        glDrawElements(GL_TRIANGLES, static_cast<int>(mesh->getIndices().size()), GL_UNSIGNED_INT, 0);
//        mesh->unbindVAO();
//        glActiveTexture(GL_TEXTURE0);
//    }
//    }
//
//
//
//}
//void Renderer::drawMap() {
//    if (activeScene->map == nullptr) return;
//    if (activeShaderProgram != activeScene->loadedMap->getShaderProgName()) {
//        activeShaderProgram = activeScene->loadedMap->getShaderProgName();
//        shaderPrograms[activeShaderProgram]->use();
//
//    }
//    applyDirectionalLight();
//    applyPointLights();
//    viewProjection();
//    shaderPrograms[activeShaderProgram]->setMat4("model",glm::mat4(1.0f));
//    shaderPrograms[activeShaderProgram]->setVec3("material.ambient", {1.0f, 0.5f, 0.31f});
//    shaderPrograms[activeShaderProgram]->setVec3("material.diffuse", {1.0f, 0.5f, 0.31f});
//    shaderPrograms[activeShaderProgram]->setVec3("material.specular", {0.1f, 0.1f, 0.1f});
//    shaderPrograms[activeShaderProgram]->setFloat("material.shininess", 32.0f);
//    shaderPrograms[activeShaderProgram]->setVec3("viewPos", activeScene->camera->position);
//    for (const auto &mesh : activeScene->loadedMap->getMeshes()) {
//        shaderPrograms[activeShaderProgram]->setBool("hasTexture",!(mesh->getTextures().empty()));
//        // bind appropriate textures
//        uint32_t diffuseNr  = 1;
//        uint32_t specularNr = 1;
//        uint32_t normalNr   = 1;
//        uint32_t heightNr   = 1;
//        for (int i=0;i<mesh->getTextures().size();i++) {
//            glActiveTexture(GL_TEXTURE0 + i);
//            std::string number;
//            std::string name = mesh->getTextures()[i].type;
//            if(name == "texture_diffuse")
//                number = std::to_string(diffuseNr++);
//            else if(name == "texture_specular")
//                number = std::to_string(specularNr++); // transfer unsigned int to string
//            else if(name == "texture_normal")
//                number = std::to_string(normalNr++); // transfer unsigned int to string
//            else if(name == "texture_height")
//                number = std::to_string(heightNr++);
//            shaderPrograms[activeShaderProgram]->setInt(name + number,i);
//            glBindTexture(GL_TEXTURE_2D, mesh->getTextures()[i].id);
//        }
//        mesh->bindVAO();
//        glDrawElements(GL_TRIANGLES, static_cast<int>(mesh->getIndices().size()), GL_UNSIGNED_INT, 0);
//        mesh->unbindVAO();
//        glActiveTexture(GL_TEXTURE0);
//    }
//}

void Renderer::update() {
    glPolygonMode(GL_FRONT_AND_BACK, debugMode ? GL_LINE : GL_FILL);
}


void Renderer::setActiveScene(Scene* scene) {
    activeScene=scene;
}
