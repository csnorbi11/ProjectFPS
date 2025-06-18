#include "headers/Camera.hpp"

#include <iostream>

#include <glm/glm.hpp>
#include <glm/ext/matrix_transform.hpp>

#include "headers/GLFWInput.hpp"


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

	printf("Camera position: %.2f, %.2f, %.2f\n", position.x, position.y, position.z);
	printf("Camera eulers: %.2f, %.2f, %.2f\n", getEulerAngles().x, getEulerAngles().z, getEulerAngles().z);
}

void Camera::recieveInput(GLFWwindow* window)
{
	direction = glm::vec3(0.f);
    if (glfwGetKey(window,GLFW_KEY_W)==GLFW_PRESS) {
        direction += forward * 3.f;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        direction -= forward * 3.f;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        direction -= right * 3.f;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        direction += right * 3.f;
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS) {
        direction.y += 3.f;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS) {
        direction.y -= 1;
    }

	double mouseX, mouseY;
	glfwGetCursorPos(window, &mouseX, &mouseY);


    offsetX = static_cast<float>(mouseX) - prevMousePosX;
    offsetY = prevMousePosY - static_cast<float>(mouseY);

    prevMousePosX = mouseX;
    prevMousePosY = mouseY;
}




glm::mat4 Camera::getViewMatrix() const {
    return glm::lookAt(position, position + forward, up);
}

