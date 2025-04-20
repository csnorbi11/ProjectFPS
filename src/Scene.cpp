#include "headers/Scene.hpp"

#include "headers/Camera.hpp"
#include "headers/GameObject.hpp"

void Scene::update(double deltaTime) {
    for (auto& gameObject : gameObjects) {
        gameObject->update(static_cast<float>(deltaTime));
    }
    camera->update(static_cast<float>(deltaTime));
}
