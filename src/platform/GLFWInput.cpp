
#include <GLFW/glfw3.h>
#include "GLFWInput.hpp"


GLFWInput::GLFWInput(GLFWwindow* window)
	: 
    window(window)
{}

GLFWInput::~GLFWInput() = default;

bool GLFWInput::toggleKey(GLFW_KEY key) {
    bool state = false;
    int keyState = glfwGetKey(window, key);
    if (keyState == GLFW_PRESS && keyState != keysPrevStates[key])
        state = true;
	keysPrevStates[key] = keyState;
    return state;
}
/**
 * @brief If the key haven't pressed yet, it's going to be added to keys and returns it's state
 * @param key the pressed key
 * @return key's state
 */
GLFW_KEY GLFWInput::getPrevKeyState(GLFW_KEY key) {
    if (keysPrevStates.count(key) == 0) {
        keysPrevStates[key] = GLFW_RELEASE;
    }

    return keysPrevStates[key];
}
void GLFWInput::update() {
    glfwGetCursorPos(window, &mousePosX, &mousePosY);

    
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