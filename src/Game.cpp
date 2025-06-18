#include "headers/Game.hpp"

#include <iostream>
#include <filesystem>

#include "headers/DirectionalLight.hpp"
#include "headers/Map.hpp"
#include "headers/PointLight.hpp"
#include "headers/Renderer.hpp"
#include "headers/Scene.hpp"


Game::Game(const WindowType windowType) {
    windowHandler = createWindowHandler(windowType);
    renderer = std::make_unique<Renderer>();

    renderer->createShaderProgram("basic",
                                  "assets/shaders/vertex.glsl",
                                  "assets/shaders/fragment.glsl");
    renderer->createShaderProgram("pointLight",
                                    "assets/shaders/pointLightVertex.glsl",
                                    "assets/shaders/pointLightFragment.glsl");

    scene = std::make_unique<Scene>();

    scene->camera= std::make_unique<Camera>();
    scene->loadedMap = std::make_unique<Map>("assets/models/TestMap.obj");

    scene->gameObjects.emplace_back(std::make_unique<GameObject>(GameObjectParams{"assets/models/backpack/backpack.obj"}));
    scene->gameObjects[0]->position=glm::vec3(30.f,1.f,6.f);
    scene->gameObjects.emplace_back(std::make_unique<GameObject>(GameObjectParams{"assets/models/backpack/backpack.obj"}));
    scene->gameObjects[1]->position=glm::vec3(30.f,1.f,-6.f);

    

    scene->camera->position=glm::vec3(25.0f,0.0f,0.0f);

    scene->directionalLight = std::make_unique<DirectionalLight>();
    scene->directionalLight->setIntensity(0.5f);
    scene->directionalLight->setAmbient({1.f,1.f,1.f});
    scene->directionalLight->setDiffuse({ 1.f,1.f,1.f });
    scene->directionalLight->setSpecular({ 1.f,1.f,1.f });

    scene->pointLights.emplace_back(std::make_unique<PointLight>(PointLightParams{static_cast<uint32_t>(scene->pointLights.size()),
        1.f,0.14,0.07}));
    scene->pointLights[0]->position=glm::vec3(35.0f,4.0f,5.0f);
    scene->pointLights[0]->setOverallColor({0.3f,0.9f,1.f});

    scene->pointLights.emplace_back(std::make_unique<PointLight>(PointLightParams{static_cast<uint32_t>(scene->pointLights.size()),
        1.f,0.22f,.20f}));
    scene->pointLights[1]->position=glm::vec3(26.0f,1.0f,-2.0f);
    scene->pointLights[1]->setOverallColor({1.0f,0.3f,0.f});
    scene->pointLights.emplace_back(std::make_unique<PointLight>(PointLightParams{static_cast<uint32_t>(scene->pointLights.size()),
        1.f,0.22f,.20f}));
    scene->pointLights[2]->position=glm::vec3(22.0f,3.0f,-2.0f);
    scene->pointLights[2]->setOverallColor({1.0f,0.9f,0.f});

    renderer->setActiveScene(scene.get());
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
    glClearColor(0.7f, 0.7f, 0.7f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    renderer->drawScene();

    windowHandler->swapBuffers();
}

void Game::input() const {
    if (WindowHandler::getKeyState(Input::Key::ESCAPE) == Input::Action::PRESSED) {
        windowHandler->closeWindow();
    }
    if (WindowHandler::toggleKey(Input::Key::L)) {
        WindowHandler::lockCursor=!WindowHandler::lockCursor;
    }

    windowHandler->pollEvents();
}

void Game::gameLoop() {
    while (!windowHandler->shouldClose()) {
        frameStart = std::chrono::high_resolution_clock::now();

        scene->update(deltaTime);
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
