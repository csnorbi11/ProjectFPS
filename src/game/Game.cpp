#include "Game.hpp"

#include <iostream>
#include <filesystem>

#include "../scene/DirectionalLight.hpp"
#include "../scene/Map.hpp"
#include "../scene/PointLight.hpp"
#include "../graphics/Renderer.hpp"
#include "../scene/Scene.hpp"
#include "../platform/GLFWInput.hpp"
#include "../platform/GLFWHandler.hpp"
#include "../scene/Camera.hpp"


Game::Game() {


    glfwHandler = std::make_unique<GLFWHandler>();
    glfwInput = std::make_unique<GLFWInput>(glfwHandler->getWindow());
    renderer = std::make_unique<Renderer>(*glfwHandler.get());

    renderer->createShaderProgram("basic",
                                  "assets/shaders/vertex.glsl",
                                  "assets/shaders/fragment.glsl");
    renderer->createShaderProgram("pointLight",
                                    "assets/shaders/pointLightVertex.glsl",
                                    "assets/shaders/pointLightFragment.glsl");

    scene = std::make_unique<Scene>();

    scene->camera= std::make_unique<Camera>();
    scene->map = std::make_unique<Map>();


    scene->camera->position = glm::vec3(25.0f, 0.0f, 0.0f);

    renderer->setActiveScene(scene.get());
}

Game::~Game() = default;

void Game::run() {
    gameLoop();
}

void Game::render() const {
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->drawScene();

    
    glfwHandler->swapBuffers();
}

void Game::input() {
    if (glfwGetKey(glfwHandler->getWindow(),GLFW_KEY_ESCAPE)) {
        glfwHandler->closeWindow();
    }
    if (glfwInput->toggleKey(GLFW_KEY_L)) {
        glfwHandler->lockCursor=!glfwHandler->lockCursor;
    }
	scene->camera->recieveInput(glfwHandler->getWindow());

    glfwHandler->pollEvents();
}

void Game::gameLoop() {
    while (!glfwHandler->shouldClose()) {
        frameStart = std::chrono::high_resolution_clock::now();
        input();

        scene->update(deltaTime);
        renderer->update();
        render();      
        calculateDeltaTime();
    }
}

void Game::calculateDeltaTime() {
    frameEnd = std::chrono::high_resolution_clock::now();
    frameDuration = std::chrono::duration_cast<std::chrono::microseconds>(frameEnd - frameStart).count();
    deltaTime = static_cast<double>(frameDuration) / 1000 / 1000; //microsec->millisec->sec
}
