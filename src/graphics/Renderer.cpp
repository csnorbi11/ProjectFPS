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
    activeScene->map->getDirectionalLight().apply(activePorgram);
}

void Renderer::applyPointLights() {
    activePorgram->setInt(
        "activePointLights",static_cast<int>(activeScene->map->getPointLights().size()));
    for (auto& light:activeScene->map->getPointLights()) {
        light->apply(activePorgram);
    }
    for (auto& light : activeScene->dynamicLights) {
        light->apply(activePorgram);
    }
}

void Renderer::drawObjects()
{
    if (activePorgram) {
        viewProjection();
        applyDirectionalLight();
        applyPointLights();
        activePorgram->setVec3("viewPos", activeScene->camera->position);
    }
    for (const auto& cmd : renderQueue) {
        if (!cmd.mesh)
            continue;

        if (cmd.mesh != activeMesh) {
            activeMesh = cmd.mesh;
            activeMesh->bindVAO();   
        }

        if (activePorgram != cmd.material->getProgram()) {
            activePorgram = cmd.material->getProgram();
            activePorgram->use();

            viewProjection();
            applyDirectionalLight();
            applyPointLights();
            activePorgram->setVec3("viewPos", activeScene->camera->position);
            
        }
        if (cmd.material != activeMaterial) {
            activeMaterial = cmd.material;

            activeMaterial->apply();
        }

        
        
        if (activePorgram) {
            activePorgram->setMat4("model", cmd.transform);
            glDrawElements(GL_TRIANGLES, static_cast<int>(cmd.mesh->getIndices().size()), GL_UNSIGNED_INT, 0);
        }
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
            if (!mesh.get() || !mesh->getMaterial())
                continue;
            renderQueue.push_back({&model->getPath(), mesh.get(),mesh->getMaterial(),object->getTransform()});
        }
    }
    std::sort(renderQueue.begin(), renderQueue.end(), [](const RenderCommand& a, const RenderCommand& b) {
        if (a.material->getProgram() != b.material->getProgram())
            return a.material->getProgram() < b.material->getProgram();
        if (a.material != b.material)
            return a.material < b.material;
        return a.mesh < b.mesh;
        });

}



void Renderer::drawScene() {
    std::vector<GameObject*>& gameObjects = activeScene->getAllObjects();
    feedRenderQueue(gameObjects);
    drawObjects();
}



void Renderer::viewProjection() {
    activePorgram->setMat4("projection", glm::perspective(glm::radians(90.0f), glfwHandler.getAspectRatio(),0.01f,100.0f));
    activePorgram->setMat4("view",activeScene->camera->getViewMatrix());
}

void Renderer::update() {
    glPolygonMode(GL_FRONT_AND_BACK, debugMode ? GL_LINE : GL_FILL);
}


void Renderer::setActiveScene(Scene* scene) {
    activeScene=scene;
}
