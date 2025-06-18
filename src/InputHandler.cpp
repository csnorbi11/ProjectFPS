#include "headers/InputHandler.hpp"


InputHandler::InputHandler(double* mousePosX, double* mousePosY)
	: 
    mousePosX(*mousePosX),
    mousePosY(*mousePosY)
{}

bool InputHandler::toggleKey(Input::Key key) {
    bool state = false;
    if (keys[key] == Input::Action::PRESSED && keys[key] != keysPrevStates[key])
        state = true;
    return state;
}
/**
 * @brief If the key haven't pressed yet, it's going to be added to keys and returns it's state
 * @param key the pressed key
 * @return key's state
 */
Input::Action InputHandler::getKeyState(const Input::Key key) {
    if (keys.count(key) == 0) {
        keys[key] = Input::Action::RELEASED;
        keysPrevStates[key] = Input::Action::RELEASED;
    }
    switch (glfwGetKey(glfwGetCurrentContext(), Input::getGLFWKeyFromKey(key))) {
    case GLFW_PRESS:
		keys[key] = Input::Action::PRESSED;
        break;
    case GLFW_RELEASE:
        keys[key] = Input::Action::RELEASED;
        break;
    case GLFW_REPEAT:
        keys[key] = Input::Action::HELD;
        break;
	default:
        break;
    }
    return keys[key];
}

Input::Action InputHandler::getKeyPrevState(Input::Key key) {
    return keysPrevStates[key];
}
void InputHandler::updateKeyStates()
{
	for (auto& key : keys) {
		keysPrevStates[key.first] = key.second;
	}
}
/**
 * @brief If the button haven't pressed yet, it's going to be added to mouseButtons and returns it's state
 * @param button the pressed button
 * @return button's state
 */
Input::Action InputHandler::getMouseButtonState(const uint8_t button) {
    if (mouseButtons.count(button) == 0) {
        mouseButtons[button] = Input::Action::RELEASED;
    }
    return mouseButtons[button];
}

double InputHandler::getMouseScrollX() {
    return 0;
}

double InputHandler::getMouseScrollY() {
    return 0;
}

double InputHandler::getMouseX() {
    return mousePosX;
}

double InputHandler::getMouseY() {
    return mousePosY;
}

void InputHandler::resetMouseScroll() {
    //mouseScrollX = 0.0f;
    //mouseScrollY = 0.0f;
}