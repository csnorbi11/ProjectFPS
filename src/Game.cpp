#include "headers/Game.hpp"

#include <iostream>

Game::Game(const WindowType windowType)
{
    windowHandler=createWindowHandler(windowType);
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


void Game::gameLoop() const {
    while (!windowHandler->shouldClose()) {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);



        windowHandler->swapBuffers();
        windowHandler->pollEvents();
    }


}
