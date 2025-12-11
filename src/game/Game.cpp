#include "Game.hpp"

#include "scene/Map.hpp"
#include "graphics/Renderer.hpp"
#include "scene/Scene.hpp"
#include "platform/GLFWInput.hpp"
#include "platform/GLFWHandler.hpp"
#include "scene/Camera.hpp"
#include "AssetManager.hpp"


Game::Game() {


    glfwHandler = std::make_unique<GLFWHandler>();
    glfwInput = std::make_unique<GLFWInput>(glfwHandler->getWindow());
	assetManager = std::make_unique<AssetManager>();
    

    assetManager->createShaderProgram("lit",
                                  "assets/shaders/lit_vertex.glsl",
                                  "assets/shaders/lit_fragment.glsl");
    assetManager->createShaderProgram("unlit",
                                    "assets/shaders/unlit_vertex.glsl",
                                    "assets/shaders/unlit_fragment.glsl");

    assetManager->createMaterial("pointLight", "unlit", {}, {});


    scene = std::make_unique<Scene>("E:/lvl1.txt",*assetManager);

    scene->camera= std::make_unique<Camera>();

    assetManager->createMaterial("golden", "lit",
        { {0.24725f, 0.1995f, 0.0745f},{0.75164f, 0.60648f, 0.22648f},{0.62828f, 0.5558f, 0.366065f},51.2f }, {});
    assetManager->getModel("cube.obj")->getMeshes()["mesh_Cube"]->changeMaterial(assetManager->getMaterials()["golden"].get());
    assetManager->createMaterial("blue", "lit",
        { {0.2f, 0.2f,1.f},{0.2f, 0.2f,1.f},{0.2f, 0.2f,1.f},2.f }, {});
    scene->map->getObjects()[scene->map->getObjects().size() - 1]->overrideMaterial("mesh_Cube", assetManager->getMaterials()["blue"].get());



    scene->camera->position = glm::vec3(25.0f, 0.0f, 0.0f);
    renderer = std::make_unique<Renderer>(*glfwHandler.get(), *assetManager.get());
    renderer->setActiveScene(scene.get());
}

Game::~Game() = default;

void Game::run() {
    gameLoop();
}

void Game::render() const {
    glClearColor(0.9, 0.9, 0.92,1.f);
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
