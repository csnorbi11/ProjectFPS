#include "headers/Scene.hpp"

#include <GLFW/glfw3.h>

#include "headers/Camera.hpp"
#include "headers/GameObject.hpp"

void Scene::update(double deltaTime) {
    for (auto& gameObject : gameObjects) {
        gameObject->update(static_cast<float>(deltaTime));
    }
    gameObjects[1]->rotation.x += static_cast<float>(deltaTime);
    camera->update(static_cast<float>(deltaTime));
}
