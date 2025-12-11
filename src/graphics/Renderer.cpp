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
    glGenBuffers(1, &instanceVBO);

    for (auto& [name, modelPtr] : assetManager.getModels()) {
        if (!modelPtr) continue; // Biztonsági ellenőrzés

        for (auto& mesh : modelPtr->getMeshes()) {
            mesh->setupInstancing(instanceVBO);
        }
    }
}

Renderer::~Renderer() {
    glDeleteBuffers(1, &instanceVBO);
    activeScene=nullptr;
}

void Renderer::applyDirectionalLight() {
    activeScene->map->getDirectionalLight().apply(activeProgram);
}

void Renderer::applyPointLights() {
    activeProgram->setInt(
        "activePointLights",static_cast<int>(activeScene->map->getPointLights().size()));
    for (auto& light:activeScene->map->getPointLights()) {
        light->apply(activeProgram);
    }
    for (auto& light : activeScene->dynamicLights) {
        light->apply(activeProgram);
    }
}

void Renderer::drawObjects()
{
    std::vector<glm::mat4> batchTransforms;
    
    activeMaterial = nullptr;
    activeMesh = nullptr;

    for (const auto& cmd : renderQueue) {
        bool materialDiffers = (activeMaterial != cmd.material);
        bool meshDiffers = (activeMesh != cmd.mesh);


        if ((materialDiffers || meshDiffers) && !batchTransforms.empty()) {
            activeProgram->setVec3("viewPos", activeScene->camera->position);
            viewProjection();
            applyDirectionalLight();
            applyPointLights();
            
            glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
            glBufferData(GL_ARRAY_BUFFER, batchTransforms.size() * sizeof(glm::mat4), batchTransforms.data(), GL_STREAM_DRAW);

            if (activeMesh) {
                glDrawElementsInstanced(GL_TRIANGLES, activeMesh->getIndices().size(), GL_UNSIGNED_INT, 0, batchTransforms.size());
            }

            batchTransforms.clear();
        }

        if (materialDiffers) {
            activeMaterial = cmd.material;
            if (activeMaterial) {
                activeMaterial->apply();
                if (activeProgram != activeMaterial->getProgram()) {
                    activeProgram = activeMaterial->getProgram();
                    activeProgram->use();

                    

                    
                }
            }
        }

        if (meshDiffers) {
            activeMesh = cmd.mesh;
            if (activeMesh) {
                activeMesh->bindVAO();
            }
        }

        batchTransforms.push_back(cmd.transform);
    }

    if (!batchTransforms.empty() && activeMesh) {
        glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
        glBufferData(GL_ARRAY_BUFFER, batchTransforms.size() * sizeof(glm::mat4), batchTransforms.data(), GL_STREAM_DRAW);

        glDrawElementsInstanced(GL_TRIANGLES, activeMesh->getIndices().size(), GL_UNSIGNED_INT, 0, batchTransforms.size());
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
        size_t i = 0;
        for (const auto& mesh : model->getMeshes()) {
            Material* mat = nullptr;
            if (!object->getOverriderMaterial().empty() && object->getOverriderMaterial()[i]) {
                mat = object->getOverriderMaterial()[i];
                i++;
            }
            else {
                mat = mesh->getMaterial();
            }
            if (!mesh.get() || !mesh->getMaterial())
                continue;
            renderQueue.push_back({&model->getName(), mesh.get(),mat,object->getTransform()});
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
    activeProgram->setMat4("projection", glm::perspective(glm::radians(90.0f), glfwHandler.getAspectRatio(),0.01f,100000.f));
    activeProgram->setMat4("view",activeScene->camera->getViewMatrix());
}

void Renderer::update() {
    glPolygonMode(GL_FRONT_AND_BACK, debugMode ? GL_LINE : GL_FILL);
}


void Renderer::setActiveScene(Scene* scene) {
    activeScene=scene;
}
