#include "Renderer.hpp"

#include <iostream>

#include "../scene/Camera.hpp"
#include "../scene/DirectionalLight.hpp"
#include "../scene/GameObject.hpp"
#include "../scene/Map.hpp"
#include "Model.hpp"
#include "../scene/PointLight.hpp"
#include "../scene/Scene.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "../platform/GLFWInput.hpp"
#include "../platform/GLFWHandler.hpp"


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

void Renderer::update() {
    glPolygonMode(GL_FRONT_AND_BACK, debugMode ? GL_LINE : GL_FILL);
}


void Renderer::setActiveScene(Scene* scene) {
    activeScene=scene;
}

std::unordered_map<std::string, std::unique_ptr<Model>>& Renderer::getModels()
{
    return models;
}
