#include "headers/Camera.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "headers/WindowHandler.hpp"
#include "headers/Input.hpp"


Camera::Camera()
    :
    GameObject({})
{
}

Camera::~Camera()=default;


void Camera::update(float deltaTime)
{

	position += direction * deltaTime;
    
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

void Camera::recieveInput(Input::IInput& input)
{
	direction = glm::vec3(0.f);
    if (input.getKeyState(Input::Key::W) == Input::Action::PRESSED) {
        direction += forward * 3.f;
    }
    if (input.getKeyState(Input::Key::S) == Input::Action::PRESSED) {
        direction -= forward * 3.f;
    }
    if (input.getKeyState(Input::Key::A) == Input::Action::PRESSED) {
        direction -= right * 3.f;
    }
    if (input.getKeyState(Input::Key::D) == Input::Action::PRESSED) {
        direction += right * 3.f;
    }
    if (input.getKeyState(Input::Key::SPACE) == Input::Action::PRESSED) {
        direction.y += 3.f;
    }
    if (input.getKeyState(Input::Key::LCTRL) == Input::Action::PRESSED) {
        direction.y -= 1;
    }

    offsetX = static_cast<float>(input.getMouseX()) - prevMousePosX;
    offsetY = prevMousePosY - static_cast<float>(input.getMouseY());

    prevMousePosX = input.getMouseX();
    prevMousePosY = input.getMouseY();
}




glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + forward, up);
}

