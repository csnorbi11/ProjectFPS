#include "headers/Game.hpp"

#include <iostream>
#include <chrono>

#include <glm/glm.hpp>

Game::Game(const WindowType windowType)
    : frameDuration(0),
      deltaTime(0) {
    windowHandler = createWindowHandler(windowType);
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

void Game::gameLoop() {
    float red = 0.f;
    float green = 0.f;
    float blue = 0.f;
    while (!windowHandler->shouldClose()) {
        frameStart = std::chrono::high_resolution_clock::now();
        glClearColor(red, green, blue, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        if (WindowHandler::getKeyState(GLFW_KEY_W) == GLFW_REPEAT) {
            red += deltaTime;
        } else if (WindowHandler::getKeyState(GLFW_KEY_S) == GLFW_REPEAT) {
            red -= deltaTime;
        }
        if (WindowHandler::getKeyState(GLFW_KEY_D) == GLFW_REPEAT) {
            blue += deltaTime;
        } else if (WindowHandler::getKeyState(GLFW_KEY_A) == GLFW_REPEAT) {
            blue -= deltaTime;
        }
        if (WindowHandler::getMouseButtonState(GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS) {
            green += deltaTime;
        } else if (WindowHandler::getMouseButtonState(GLFW_MOUSE_BUTTON_RIGHT) == GLFW_PRESS) {
            green -= deltaTime;
        }


        windowHandler->swapBuffers();
        windowHandler->pollEvents();
        calculateDeltaTime();

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
