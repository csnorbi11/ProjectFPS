#include "headers/WindowHandler.hpp"

#include <cstdint>

std::unordered_map<uint16_t, uint8_t> WindowHandler::keys = {};
std::unordered_map<uint8_t, uint8_t> WindowHandler::mouseButtons = {};
double WindowHandler::mouseScrollx = 0.0f;
double WindowHandler::mouseScrolly = 0.0f;
double WindowHandler::mousePosx = 0.0;
double WindowHandler::mousePosy = 0.0;

/**
 * @brief If the key haven't pressed yet, it's going to be added to keys and returns it's state
 * @param key the pressed key
 * @return key's state
 */
uint8_t WindowHandler::getKeyState(const uint16_t key) {
    if (keys.count(key) == 0) {
        keys[key] = GLFW_RELEASE;
    }
    return keys[key];
}

/**
 * @brief If the button haven't pressed yet, it's going to be added to mouseButtons and returns it's state
 * @param button the pressed button
 * @return button's state
 */
uint8_t WindowHandler::getMouseButtonState(const uint8_t button) {
    if (mouseButtons.count(button) == 0) {
        mouseButtons[button] = GLFW_RELEASE;
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
