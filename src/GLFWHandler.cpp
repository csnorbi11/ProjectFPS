#include "headers/GLFWHandler.hpp"

#include <iostream>
#include <memory>
#include <ostream>


#include "headers/DebugMode.hpp"
#include "headers/Game.hpp"
#include "headers/Input.hpp"


std::unique_ptr<GLFWwindow, GLFWDestroyer> GLFWHandler::window = nullptr;


GLFWHandler::GLFWHandler(int width, int height){
    if (window != nullptr)
        throw std::runtime_error("Already have window");
    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    window = std::unique_ptr<GLFWwindow, GLFWDestroyer>
            (glfwCreateWindow(width, height, "GLFW Window", nullptr, nullptr));
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }


    glfwMakeContextCurrent(window.get());

    glfwSetFramebufferSizeCallback(window.get(), InputHandler::framebufferSizeCallback);
    glfwSetKeyCallback(window.get(), InputHandler::keyCallback);
    glfwSetCursorPosCallback(window.get(), InputHandler::cursorPositionCallback);
    glfwSetMouseButtonCallback(window.get(), InputHandler::mouseButtonCallback);
    glfwSetScrollCallback(window.get(), InputHandler::scrollCallback);

    if (!gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress))) {
        throw std::runtime_error("Failed to initialize GLAD");
    }
    glfwSwapInterval(0);
    glEnable(GL_DEPTH_TEST);


    std::cout << glGetString(GL_RENDERER) << std::endl;
}

GLFWHandler::~GLFWHandler()=default;

bool GLFWHandler::shouldClose() {
    return glfwWindowShouldClose(window.get());
}

void GLFWHandler::swapBuffers() {
    glfwPollEvents();
}

void GLFWHandler::pollEvents() {
    glfwSwapBuffers(window.get());
}

void GLFWHandler::closeWindow() {
    glfwSetWindowShouldClose(window.get(), GLFW_TRUE);
}


void GLFWHandler::InputHandler::keyCallback(GLFWwindow *window, const int key, const int scancode, const int action,
                                            const int mods) {
    Input::Key convertedKey=Input::getKeyGLFW(key);
    if (inputDebugMode & InputDebugMode::Key)
        debugKeys(key, scancode, action, mods);
    if (action == GLFW_PRESS)
        keys[convertedKey] = Input::Action::PRESSED;
    else if (action == GLFW_RELEASE)
        keys[convertedKey] = Input::Action::RELEASED;
    else if (action == GLFW_REPEAT)
        keys[convertedKey] = Input::Action::HELD;
}

void GLFWHandler::InputHandler::cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
    if (inputDebugMode & InputDebugMode::MouseCursor)
        debugCursor(xPos, yPos);

    mousePosX = xPos;
    mousePosY = yPos;

}

void GLFWHandler::InputHandler::mouseButtonCallback(GLFWwindow *window, const int button, const int action,
                                                    const int mods) {
    std::cout<<button<<std::endl;
    if (inputDebugMode & InputDebugMode::MouseButton)
        debugMouseButton(button, action, mods);
    if (action == GLFW_PRESS)
        mouseButtons[button] = Input::Action::PRESSED;
    else if (action == GLFW_RELEASE)
        mouseButtons[button] = Input::Action::RELEASED;
    else if (action == GLFW_REPEAT)
        mouseButtons[button] = Input::Action::HELD;
}

void GLFWHandler::InputHandler::scrollCallback(GLFWwindow *window, const double xOffset, const double yOffset) {
    if (inputDebugMode & InputDebugMode::MouseScroll)
        debugMouseScroll(xOffset, yOffset);
    mouseScrollX = xOffset;
    mouseScrollY = yOffset;
}

void GLFWHandler::InputHandler::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
    WindowHandler::width = width;
    WindowHandler::height = height;
    aspectRatio = static_cast<float>(width) / static_cast<float>(height);
}

void GLFWHandler::InputHandler::debugMouseScroll(const double xOffset, const double yOffset) {
    std::cout << "Scroll: " << xOffset << " " << yOffset << std::endl;
}

void GLFWHandler::InputHandler::debugMouseButton(const int button, const int action, const int mods) {
    if (action == GLFW_PRESS)
        std::cout << "Mouse button: " << button << " " << mods << std::endl;
    if (action == GLFW_RELEASE)
        std::cout << "Mouse button: " << button << " " << mods << std::endl;
}

void GLFWHandler::InputHandler::debugCursor(const double xPos, const double yPos) {
    std::cout << "Cursor position: " << xPos << " " << yPos << std::endl;
}

void GLFWHandler::InputHandler::debugKeys(const int key, const int scancode, const int action, const int mods) {
    std::cout << key << " " << scancode << " " << action << " " << mods << std::endl;
    std::cout << "scancode:" << glfwGetKeyScancode(key) << std::endl;
    if (action == GLFW_PRESS)
        std::cout << glfwGetKeyName(key, scancode) << " is pressed";
    if (action == GLFW_RELEASE)
        std::cout << glfwGetKeyName(key, scancode) << " is released";
    if (mods & GLFW_MOD_SHIFT)
        std::cout << " with SHIFT";
    if (mods & GLFW_MOD_CONTROL)
        std::cout << " with CONTROL";
    if (mods & GLFW_MOD_ALT)
        std::cout << " with ALT";
    std::cout << std::endl;
}
