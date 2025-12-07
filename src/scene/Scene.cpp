#include "Scene.hpp"

#include <iostream>
#include <ostream>
#include <GLFW/glfw3.h>

#include "Camera.hpp"
#include "GameObject.hpp"
#include "PointLight.hpp"

void Scene::update(double deltaTime) {

    camera->update(static_cast<float>(deltaTime));
}

std::vector<GameObject*> Scene::getAllObjects() const
{

    size_t size = map->getObjects().size() + map->getPointLights().size() +
        dynamicLights.size() + enemies.size() + dynamicLights.size();

    std::vector<GameObject*> objects{size};

    for (auto& obj : map->getObjects()) {
        objects.push_back(obj.get());
    }
    for (auto& obj : map->getPointLights()) {
        objects.push_back(obj.get());
    }

    for (auto& obj : dynamicLights) {
        objects.push_back(obj.get());
    }
    for (auto& obj : enemies) {
        objects.push_back(obj.get());
    }
    for (auto& obj : dynamicObjects) {
        objects.push_back(obj.get());
    }

    return objects;
}
