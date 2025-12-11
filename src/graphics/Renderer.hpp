#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <unordered_map>
#include <glad/glad.h>
#include <string>

#include "../scene/Light.hpp"
#include "../scene/Scene.hpp"
#include "../platform/GLFWHandler.hpp"
#include "../game/AssetManager.hpp"
#include "RenderCommand.hpp"


class Renderer {
public:
    Renderer(GLFWHandler& glfwHandler, AssetManager& assetManager);
    ~Renderer();


    void drawScene();
    void update();

    void setActiveScene(Scene* scene);
private:

    void viewProjection();
    void applyDirectionalLight();
    void applyPointLights();

    void drawObjects();

    void feedRenderQueue(std::vector<GameObject*>& gameObjects);

    std::vector<RenderCommand> renderQueue;
    unsigned int instanceVBO;
    
    ShaderProgram* activeProgram = nullptr;
    Scene* activeScene=nullptr;
    Mesh* activeMesh = nullptr;
    Material* activeMaterial = nullptr;

    bool debugMode=false;

    GLFWHandler& glfwHandler;
	AssetManager& assetManager;

};

#endif //RENDERER_HPP