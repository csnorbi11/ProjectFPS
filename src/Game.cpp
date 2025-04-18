#include "headers/Game.hpp"

#include <iostream>
#include <filesystem>

#include "headers/Renderer.hpp"


Game::Game(const WindowType windowType)
{
    windowHandler = createWindowHandler(windowType);
    renderer = std::make_unique<Renderer>();

    renderer->createShaderProgram("basic",
                                  "assets/shaders/vertex.glsl",
                                  "assets/shaders/fragment.glsl");

    camera= std::make_unique<Camera>();
    renderer->setActiveCamera(camera.get());
    loadedMap = std::make_unique<Map>("assets/models/TestMap.obj");
    renderer->setActiveMap(loadedMap.get());

    gameObjects.emplace_back(std::make_unique<GameObject>("assets/models/backpack/backpack.obj"));
    gameObjects[0]->position=glm::vec3(30.f,1.f,6.f);

    camera->position=glm::vec3(25.0f,0.0f,0.0f);
}

Game::~Game() = default;

void Game::run() {
    gameLoop();
}

std::unique_ptr<WindowHandler> Game::createWindowHandler(const WindowType windowType,
    int windowWidth,int windowHeight) {
    switch (windowType) {
        case WindowType::GLFW:
            return std::make_unique<GLFWHandler>(windowWidth,windowHeight);
        default:
            throw std::runtime_error("Invalid Window Type");
    }
}

void Game::render() const {
    glClearColor(0.f, 0.2f, 0.2f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->drawMap();
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

        for (const auto& gameObject : gameObjects) {
            gameObject->update(static_cast<float>(deltaTime));
        }
        camera->update(static_cast<float>(deltaTime));
        renderer->update();
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
