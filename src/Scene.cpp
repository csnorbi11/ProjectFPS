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
    gameObjects[1]->rotateEulerX(glm::abs(glm::sin(deltaTime))*10);
	gameObjects[0]->rotate(glm::vec3(0.f, 1.f, 1.f), static_cast<float>(deltaTime) * 10.f);
    pointLights[1]->position.z = glm::sin(glfwGetTime()*5.f)*5.f;
    camera->update(static_cast<float>(deltaTime));
}
