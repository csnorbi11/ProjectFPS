#include "headers/InputHandler.hpp"

bool InputHandler::toggleKey(Input::Key key) {
    bool state = false;
    if (keys[key] == Input::Action::PRESSED && keys[key] != keysPrevStates[key])
        state = true;
    keysPrevStates[key] = keys[key];
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
    return keys[key];
}

Input::Action InputHandler::getKeyPrevState(Input::Key key) {
    return keysPrevStates[key];
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
    return mouseScrollX;
}

double InputHandler::getMouseScrollY() {
    return mouseScrollY;
}

double InputHandler::getMouseX() {
    return mousePosX;
}

double InputHandler::getMouseY() {
    return mousePosY;
}

void InputHandler::resetMouseScroll() {
    mouseScrollX = 0.0f;
    mouseScrollY = 0.0f;
}