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
