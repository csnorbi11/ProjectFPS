#include "Renderer.hpp"

#include <iostream>

#include "../scene/Camera.hpp"
#include "../scene/DirectionalLight.hpp"
#include "../scene/GameObject.hpp"
#include "../scene/Map.hpp"
#include "Model.hpp"
#include "../scene/PointLight.hpp"
#include "../scene/Scene.hpp"
#include "ShaderProgram.hpp"
#include "../platform/GLFWInput.hpp"
#include "../platform/GLFWHandler.hpp"


Renderer::Renderer(GLFWHandler& glfwHandler, AssetManager& assetManager)
    :
    glfwHandler(glfwHandler),
    assetManager(assetManager)
{
    
}

Renderer::~Renderer() {
    activeScene=nullptr;
}

void Renderer::applyDirectionalLight() {
    activeScene->map->getDirectionalLight().apply(assetManager.getShaderPrograms()["basic"].get());
}

void Renderer::applyPointLights() {
    assetManager.getShaderPrograms()["basic"].get()->setInt(
        "activePointLights",static_cast<int>(activeScene->map->getPointLights().size()));
    for (auto& light:activeScene->map->getPointLights()) {
        light->apply(assetManager.getShaderPrograms()["basic"].get());
    }
    for (auto& light : activeScene->dynamicLights) {
        light->apply(assetManager.getShaderPrograms()["basic"].get());
    }
}

void Renderer::drawObjects(const std::vector<GameObject*>& objects)
{
    activeVAO = 0;
    activeShaderProgram = "basic";
    assetManager.getShaderPrograms()[activeShaderProgram]->use();
    assetManager.getShaderPrograms()[activeShaderProgram]->setVec3("viewPos", activeScene->camera->position);
    viewProjection();
    applyDirectionalLight();
    applyPointLights();


    assetManager.getShaderPrograms()[activeShaderProgram]->setVec3("material.ambient", { 1.0f, 0.5f, 0.31f });
    assetManager.getShaderPrograms()[activeShaderProgram]->setVec3("material.diffuse", { 1.0f, 0.5f, 0.31f });
    assetManager.getShaderPrograms()[activeShaderProgram]->setVec3("material.specular", { 0.1f, 0.1f, 0.1f });
    assetManager.getShaderPrograms()[activeShaderProgram]->setFloat("material.shininess", 32.0f);
    for (auto obj : objects) {
        if (!obj||!obj->drawable()) {
            continue;
        }

        for (const auto& mesh : obj->getModel()->getMeshes()) {
            glm::mat4 transformMatrix(1.f);
            transformMatrix = glm::translate(glm::mat4(1.0f), obj->position);
            transformMatrix *= static_cast<glm::mat4>(obj->getQuaternion());
            assetManager.getShaderPrograms()[activeShaderProgram]->setMat4("model", transformMatrix);

            
            if (activeVAO != mesh->getVAO()) {
                activeVAO = mesh->getVAO();


                assetManager.getShaderPrograms()[activeShaderProgram]->setBool("hasTexture", !(mesh->getTextures().empty()));
                for (int i = 0;i < mesh->getTextures().size();i++) {
                    glActiveTexture(GL_TEXTURE0 + i);
                    std::string name = mesh->getTextures()[i].type;
                    if (name == "texture_diffuse") {
                        assetManager.getShaderPrograms()[activeShaderProgram]->setInt("material.diffuse", i);
                    }
                    else if (name == "texture_specular") {
                        assetManager.getShaderPrograms()[activeShaderProgram]->setInt("material.specular", i);
                    }


                    glBindTexture(GL_TEXTURE_2D, mesh->getTextures()[i].id);
                }



                mesh->bindVAO();
            }
            glDrawElements(GL_TRIANGLES, static_cast<int>(mesh->getIndices().size()), GL_UNSIGNED_INT, 0);

        }
    }
    glBindVertexArray(0);
}

template<>
void Renderer::drawObjects<PointLight>(std::vector<std::unique_ptr<PointLight>>& objects) {
    for (const auto& object : objects) {


        if (!isShaderProgramActive("pointLight")) {
            activeShaderProgram = "pointLight";
            assetManager.getShaderPrograms()[activeShaderProgram]->use();
        }
        assetManager.getShaderPrograms()[activeShaderProgram]->setVec3("color", object->getDiffuse());
        drawObject<PointLight>(object.get());
    }
}

void Renderer::drawMap()
{
    drawObjects(activeScene->getAllObjects());
	//drawObjects<StaticObject>(activeScene->map->getObjects());
	//drawObjects<PointLight>(activeScene->map->getPointLights());
}


void Renderer::drawScene() {
    if (activeScene==nullptr) return;
	drawMap();
}

bool Renderer::isShaderProgramActive(const std::string& programName) const
{
    return activeShaderProgram==programName;
}

void Renderer::viewProjection() {
    assetManager.getShaderPrograms()[activeShaderProgram]->setMat4("projection",
                                                 glm::perspective(glm::radians(90.0f), glfwHandler.getAspectRatio(),0.01f,100.0f));
    assetManager.getShaderPrograms()[activeShaderProgram]->setMat4("view",activeScene->camera->getViewMatrix());
}

void Renderer::update() {
    glPolygonMode(GL_FRONT_AND_BACK, debugMode ? GL_LINE : GL_FILL);
}


void Renderer::setActiveScene(Scene* scene) {
    activeScene=scene;
}
