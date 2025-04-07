#include "headers/Game.hpp"

#include <iostream>
#include <chrono>

#include <glm/glm.hpp>

#include "headers/Shader.hpp"
#include "headers/ShaderProgram.hpp"

Game::Game(const WindowType windowType)
    : frameDuration(0),
      deltaTime(0) {
    windowHandler = createWindowHandler(windowType);

    Shader vertexShader("assets/shaders/vertex.glsl", GL_VERTEX_SHADER);
    Shader fragShader("assets/shaders/fragment.glsl", GL_FRAGMENT_SHADER);
    shaderProgram=new ShaderProgram(vertexShader, fragShader);

    gameObject = new GameObject();
}

Game::~Game() = default;

void Game::run() {
    gameLoop();
}

std::unique_ptr<WindowHandler> Game::createWindowHandler(const WindowType windowType) {
    switch (windowType) {
        case WindowType::GLFW:
            return std::make_unique<GLFWHandler>();
        default:
            throw std::runtime_error("Invalid Window Type");
    }
}

void Game::render() {
    glClearColor(0.2f,0.2f,0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

    gameObject->draw(*shaderProgram);






    windowHandler->swapBuffers();
    windowHandler->pollEvents();
    calculateDeltaTime();
}

void Game::gameLoop() {
    while (!windowHandler->shouldClose()) {
        frameStart = std::chrono::high_resolution_clock::now();
        render();

        if (WindowHandler::getKeyState(GLFW_KEY_ESCAPE) == GLFW_PRESS) {
            windowHandler->closeWindow();
        }
    }
}

void Game::calculateDeltaTime() {
    frameEnd = std::chrono::high_resolution_clock::now();
    frameDuration = std::chrono::duration_cast<std::chrono::microseconds>(frameEnd - frameStart).count();
    deltaTime = static_cast<double>(frameDuration) / 1000 / 1000; //microsec->millisec->sec
}
