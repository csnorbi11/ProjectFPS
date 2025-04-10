#include "headers/WindowHandler.hpp"

#include <cstdint>

std::unordered_map<uint16_t, Input::Action> WindowHandler::keys = {};
std::unordered_map<uint8_t, Input::Action> WindowHandler::mouseButtons = {};
double WindowHandler::mouseScrollx = 0.0f;
double WindowHandler::mouseScrolly = 0.0f;
double WindowHandler::mousePosx = 0.0;
double WindowHandler::mousePosy = 0.0;

/**
 * @brief If the key haven't pressed yet, it's going to be added to keys and returns it's state
 * @param key the pressed key
 * @return key's state
 */
Input::Action WindowHandler::getKeyState(const uint16_t key) {
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

double WindowHandler::getMouseScrollx() {
    return mouseScrollx;
}

double WindowHandler::getMouseScrolly() {
    return mouseScrolly;
}

double WindowHandler::getMouseX() {
    return mousePosx;
}

double WindowHandler::getMouseY() {
    return mousePosy;
}

void WindowHandler::resetMouseScroll() {
    mouseScrollx = 0.0f;
    mouseScrolly = 0.0f;
}
