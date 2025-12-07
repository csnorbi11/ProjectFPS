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
{}

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

template<>
void Renderer::drawObjects<PointLight>(std::vector<std::unique_ptr<PointLight>>& objects) {
    for (const auto& object : objects) {

        if (object->isDrawable()) {
            if (!isShaderProgramActive("pointLight")) {
                activeShaderProgram = "pointLight";
                assetManager.getShaderPrograms()[activeShaderProgram]->use();
            }
            assetManager.getShaderPrograms()[activeShaderProgram]->setVec3("color", object->getDiffuse());
            drawObject<PointLight>(object.get());
        }


    }
}

void Renderer::drawMap()
{

	drawObjects<StaticObject>(activeScene->map->getObjects());
	drawObjects<PointLight>(activeScene->map->getPointLights());
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
