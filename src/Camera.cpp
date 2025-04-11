#include "headers/Camera.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "headers/WindowHandler.hpp"


Camera::Camera()
    :
    GameObject("none"),
    mouseSensitivity(1.f)
{

}

void Camera::update(float deltaTime)
{
    if (WindowHandler::getKeyState(Input::Key::W)==Input::Action::PRESSED) {
        position+=front*deltaTime;
    }
    if (WindowHandler::getKeyState(Input::Key::S)==Input::Action::PRESSED) {
        position-=front*deltaTime;
    }
    if (WindowHandler::getKeyState(Input::Key::A)==Input::Action::PRESSED) {
        position-=right*deltaTime;
    }
    if (WindowHandler::getKeyState(Input::Key::D)==Input::Action::PRESSED) {
        position+=right*deltaTime;
    }

    float offsetX = WindowHandler::getMouseX()-prevMousePosX;
    float offsetY = prevMousePosY-WindowHandler::getMouseY();

    prevMousePosX = WindowHandler::getMouseX();
    prevMousePosY = WindowHandler::getMouseY();

    rotation.x+=offsetY;
    rotation.y+=offsetX;


    if (rotation.x>89.0f)
        rotation.x=89.0f;
    if (rotation.x<-89.0f)
        rotation.x=-89.0f;


    updateCameraVectors();
}


glm::mat4 Camera::getViewMatrix() {
    return glm::lookAt(position, position + front, up);
}

void Camera::updateCameraVectors() {
    front.x = glm::cos(glm::radians(rotation.y)) * glm::cos(glm::radians(rotation.x));
    front.y = glm::sin(glm::radians(rotation.x));
    front.z = glm::sin(glm::radians(rotation.y)) * glm::cos(glm::radians(rotation.x));
    front = glm::normalize(front);
    right = glm::normalize(glm::cross(front, glm::vec3(0.0f, 1.0f, 0.0f)));
    up    = glm::normalize(glm::cross(right, front));
}
