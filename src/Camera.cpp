#include "headers/Camera.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "headers/WindowHandler.hpp"


Camera::Camera()
    :
    GameObject({})
{
	prevMousePosX = static_cast<float>(WindowHandler::getMouseX());
	prevMousePosY = static_cast<float>(WindowHandler::getMouseY());
}

Camera::~Camera()=default;


void Camera::update(float deltaTime)
{
    if (WindowHandler::getKeyState(Input::Key::W)==Input::Action::PRESSED) {
        position+=forward*deltaTime*3.f;
    }
    if (WindowHandler::getKeyState(Input::Key::S)==Input::Action::PRESSED) {
        position-=forward*deltaTime*3.f;
    }
    if (WindowHandler::getKeyState(Input::Key::A)==Input::Action::PRESSED) {
        position-=right*deltaTime*3.f;
    }
    if (WindowHandler::getKeyState(Input::Key::D)==Input::Action::PRESSED) {
        position+=right*deltaTime*3.f;
    }
    if (WindowHandler::getKeyState(Input::Key::SPACE)==Input::Action::PRESSED) {
        position.y+=deltaTime*3.f;
    }
    if (WindowHandler::getKeyState(Input::Key::LCTRL)==Input::Action::PRESSED) {
        position.y-=deltaTime;
    }

    const float offsetX = static_cast<float>(WindowHandler::getMouseX())-prevMousePosX;
    const float offsetY = prevMousePosY-static_cast<float>(WindowHandler::getMouseY());

    prevMousePosX = WindowHandler::getMouseX();
    prevMousePosY = WindowHandler::getMouseY();
	yaw -= offsetX * deltaTime * mouseSensitivity;
    pitch += offsetY * deltaTime * mouseSensitivity;
	if (pitch > glm::radians(89.0f)) {
		pitch = glm::radians(89.0f);
    }
    else if (pitch < glm::radians(-89.0f)) {
		pitch = glm::radians(-89.0f);
    }

    glm::quat qPitch = glm::angleAxis(pitch, glm::vec3(1.f, 0.f, 0.f));
    glm::quat qYaw = glm::angleAxis(yaw, glm::vec3(0.f, 1.f, 0.f));

	setQuaternion(glm::normalize(qYaw * qPitch));
	calculateVectors();
}


glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + forward, up);
}

