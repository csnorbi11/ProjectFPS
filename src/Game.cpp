#include "headers/Game.hpp"

#include <iostream>
#include <chrono>

#include <glm/glm.hpp>

#include "headers/Renderer.hpp"
#include "headers/ShaderProgram.hpp"

Game::Game(const WindowType windowType)
    :
    frameDuration(0),
    deltaTime(0)
{
    windowHandler = createWindowHandler(windowType);
    renderer = std::make_unique<Renderer>();

    renderer->createShaderProgram("basic",
                                  "assets/shaders/vertex.glsl",
                                  "assets/shaders/fragment.glsl");

    gameObjects.emplace_back(std::make_unique<GameObject>("cube"));
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

void Game::render() const {
    glClearColor(0.f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);


    for (auto& gameObject : gameObjects) {
        renderer->draw(*gameObject);
    }

    windowHandler->swapBuffers();


}

void Game::input() const {
    if (WindowHandler::getKeyState(Input::Key::ESCAPE) == Input::Action::PRESSED) {
        windowHandler->closeWindow();
    }

    windowHandler->pollEvents();
}

void Game::gameLoop() {
    while (!windowHandler->shouldClose()) {
        frameStart = std::chrono::high_resolution_clock::now();



        render();
        input();
        calculateDeltaTime();
    }
}

void Game::calculateDeltaTime() {
    frameEnd = std::chrono::high_resolution_clock::now();
    frameDuration = std::chrono::duration_cast<std::chrono::microseconds>(frameEnd - frameStart).count();
    deltaTime = static_cast<double>(frameDuration) / 1000 / 1000; //microsec->millisec->sec
}
