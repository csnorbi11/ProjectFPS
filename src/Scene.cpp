#include "headers/Scene.hpp"

#include <iostream>
#include <ostream>
#include <GLFW/glfw3.h>

#include "headers/Camera.hpp"
#include "headers/GameObject.hpp"
#include "headers/PointLight.hpp"

void Scene::update(double deltaTime) {
    for (auto& gameObject : gameObjects) {
        gameObject->update(static_cast<float>(deltaTime));
    }
    gameObjects[1]->rotation.x += static_cast<float>(deltaTime);
    pointLights[1]->position.z = glm::sin(glfwGetTime()*5.f)*5.f;
    camera->update(static_cast<float>(deltaTime));
}
