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

void Renderer::drawObjects()
{
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
    for (const auto& cmd : renderQueue) {
        if (!cmd.mesh)
            continue;

        if (cmd.mesh != activeMesh) {
            activeMesh = cmd.mesh;
            activeMesh->bindVAO();   
        }
        if (cmd.material != activeMaterial) {
            activeMaterial = cmd.material;
            activeMaterial->apply();
        }

        assetManager.getShaderPrograms()[activeShaderProgram]->setMat4("model", cmd.transform);

        glDrawElements(GL_TRIANGLES, static_cast<int>(cmd.mesh->getIndices().size()), GL_UNSIGNED_INT, 0);
    }

    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Renderer::feedRenderQueue(std::vector<GameObject*>& gameObjects)
{
    renderQueue.clear();

    for (auto object : gameObjects) {

        Model* model = object->getModel();
        if (!model)
            continue;
        for (const auto& mesh : model->getMeshes()) {
            renderQueue.push_back({&model->getPath(), mesh.get(),mesh->getMaterial(),object->getTransform()});
        }
    }
    std::sort(renderQueue.begin(), renderQueue.end(), [](const RenderCommand& a, const RenderCommand& b) {
        return a.mesh < b.mesh;
        });

}



void Renderer::drawScene() {
    std::vector<GameObject*>& gameObjects = activeScene->getAllObjects();
    feedRenderQueue(gameObjects);
    drawObjects();
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
