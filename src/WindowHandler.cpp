#include "headers/WindowHandler.hpp"

#include <cstdint>

std::unordered_map<Input::Key, Input::Action> WindowHandler::keys = {};
std::unordered_map<uint8_t, Input::Action> WindowHandler::mouseButtons = {};
double WindowHandler::mouseScrollX = 0.0f;
double WindowHandler::mouseScrollY = 0.0f;
double WindowHandler::mousePosX = 0.0;
double WindowHandler::mousePosY = 0.0;



WindowHandler::WindowHandler(const int width, const int height)
: width(width),
          height(height),
          aspectRatio(
              static_cast<float>(width) / static_cast<float>(height)
          ){
}

/**
 * @brief If the key haven't pressed yet, it's going to be added to keys and returns it's state
 * @param key the pressed key
 * @return key's state
 */
Input::Action WindowHandler::getKeyState(const Input::Key key) {
    if (keys.count(key) == 0) {
        keys[key] = Input::Action::RELEASED;
    }
    return keys[key];
}

/**
 * @brief If the button haven't pressed yet, it's going to be added to mouseButtons and returns it's state
 * @param button the pressed button
 * @return button's state
 */
Input::Action WindowHandler::getMouseButtonState(const uint8_t button) {
    if (mouseButtons.count(button) == 0) {
        mouseButtons[button] = Input::Action::RELEASED;
    }
    return mouseButtons[button];
}

double WindowHandler::getMouseScrollX() {
    return mouseScrollX;
}

double WindowHandler::getMouseScrollY() {
    return mouseScrollY;
}

double WindowHandler::getMouseX() {
    return mousePosX;
}

double WindowHandler::getMouseY() {
    return mousePosY;
}

void WindowHandler::resetMouseScroll() {
    mouseScrollX = 0.0f;
    mouseScrollY = 0.0f;
}
