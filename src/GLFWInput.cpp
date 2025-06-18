#include "headers/GLFWInput.hpp"


GLFWInput::GLFWInput(GLFWwindow* window)
	: 
    window(window)
{}

GLFWInput::~GLFWInput() = default;

bool GLFWInput::toggleKey(Input::Key key) {
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
Input::Action GLFWInput::getKeyState(const Input::Key key) {
    if (keys.count(key) == 0) {
        keys[key] = Input::Action::RELEASED;
        keysPrevStates[key] = Input::Action::RELEASED;
    }

    return keys[key];
}
void GLFWInput::update() {
    glfwGetCursorPos(window, &mousePosX, &mousePosY);

    for (auto& [key, action] : keys) {
		keysPrevStates[key] = action;
        switch (window, Input::mapKey(key)) {
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
    }
    
}

Input::Action GLFWInput::getMouseButtonState(const uint8_t button) {
    if (mouseButtons.count(button) == 0) {
        mouseButtons[button] = Input::Action::RELEASED;
    }
    return mouseButtons[button];
}

double GLFWInput::getMouseScrollY() {
    return mouseScrollY;
}

double GLFWInput::getMouseX() {
    return mousePosX;
}

double GLFWInput::getMouseY() {
    return mousePosY;
}

void GLFWInput::resetMouseScroll() {
    mouseScrollY = 0.0f;
}