#include "headers/Game.hpp"

#include <iostream>
#include <glm/glm.hpp>

#include "headers/DebugMode.hpp"

Game::Game(const WindowType windowType)
{
    windowHandler=createWindowHandler(windowType);

    inputDebugMode=InputDebugMode::Key;
}
Game::~Game() = default;

void Game::run() {
    gameLoop();
}

std::unique_ptr<WindowHandler> Game::createWindowHandler(WindowType windowType) {
    switch (windowType) {
        case WindowType::GLFW:
            return std::make_unique<GLFWHandler>();
        default:
            throw std::runtime_error("Invalid Window Type");
    }
}

void Game::gameLoop() {
    float red=0.f;
    float blue=0.f;
    while (!windowHandler->shouldClose()) {
        deltaTime=windowHandler->getElapsedTime()-lastFrameEnd;

        glClearColor(red, 0.f,blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (windowHandler->getKeys().at(GLFW_KEY_W)) {
            red+=deltaTime*3000;
        }else if (windowHandler->getKeys().at(GLFW_KEY_S)) {
            red-=deltaTime*3000;
        }
        if (WindowHandler::getKeys().at(GLFW_KEY_D)) {
            blue+=deltaTime*3000;
        }else if (WindowHandler::getKeys().at(GLFW_KEY_A)) {
            blue-=deltaTime*3000;
        }




        windowHandler->swapBuffers();
        windowHandler->pollEvents();
        lastFrameEnd=windowHandler->getElapsedTime();
    }


}
