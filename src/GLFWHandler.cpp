#include "headers/GLFWHandler.hpp"

#include <iostream>
#include <memory>
#include <ostream>

#include "headers/DebugMode.hpp"


std::unique_ptr<GLFWwindow, GLFWDestroyer> GLFWHandler::window = nullptr;


GLFWHandler::GLFWHandler()
    :
    WindowHandler(800,600)
{
    if (window!=nullptr)
        throw std::runtime_error("Already have window");

    if (!glfwInit()) {
        throw std::runtime_error("Failed to initialize GLFW");
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);



    window=std::unique_ptr<GLFWwindow,GLFWDestroyer>
        (glfwCreateWindow(width, height, "GLFW Window", nullptr, nullptr));
    if (window == nullptr) {
        glfwTerminate();
        throw std::runtime_error("Failed to create GLFW window");
    }



    glfwMakeContextCurrent(window.get());
    glfwSetFramebufferSizeCallback(window.get(), InputHandler::framebufferSizeCallback);
    glfwSetKeyCallback(window.get(),InputHandler::keyCallback);
    glfwSetCursorPosCallback(window.get(),InputHandler::cursorPositionCallback);
    glfwSetMouseButtonCallback(window.get(),InputHandler::mouseButtonCallback);
    glfwSetScrollCallback(window.get(),InputHandler::scrollCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        throw std::runtime_error("Failed to initialize GLAD");
    }



}

bool GLFWHandler::shouldClose() {
    return glfwWindowShouldClose(window.get());
}
void GLFWHandler::swapBuffers() {
    glfwPollEvents();
}
void GLFWHandler::pollEvents() {
    glfwSwapBuffers(window.get());
}

float GLFWHandler::getElapsedTime() {
    return glfwGetTime();
}



void GLFWHandler::InputHandler::keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    debugKeys(key, scancode, action, mods);
}
void GLFWHandler::InputHandler::cursorPositionCallback(GLFWwindow *window, double xPos, double yPos) {
    debugCursor(xPos, yPos);
}
void GLFWHandler::InputHandler::mouseButtonCallback(GLFWwindow *window, int button, int action, int mods) {
    debugMouseButton(button, action, mods);
}
void GLFWHandler::InputHandler::scrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
    debugMouseScroll(xOffset, yOffset);
}
void GLFWHandler::InputHandler::framebufferSizeCallback(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void GLFWHandler::InputHandler::debugMouseScroll(double xOffset, double yOffset) {
    if (inputDebugMode&InputDebugMode::MouseScroll) {
        std::cout<<"Scroll: "<<xOffset<<" "<<yOffset<<std::endl;
    }
}
void GLFWHandler::InputHandler::debugMouseButton(int button, int action, int mods) {
    if (inputDebugMode&InputDebugMode::MouseButton){
        if (action == GLFW_PRESS)
            std::cout<<"Mouse button: "<<button<<" "<<mods<<std::endl;
        if (action == GLFW_RELEASE)
            std::cout<<"Mouse button: "<<button<<" "<<mods<<std::endl;
    }
}
void GLFWHandler::InputHandler::debugCursor(double xPos, double yPos) {
    if (inputDebugMode&InputDebugMode::MouseCursor)
        std::cout<<"Cursor position: "<<xPos<<" "<<yPos<<std::endl;
}
void GLFWHandler::InputHandler::debugKeys(int key, int scancode, int action, int mods) {
    if (inputDebugMode&InputDebugMode::Key) {
        if (action == GLFW_PRESS)
            std::cout << glfwGetKeyName(key,scancode) << " is pressed";
        if (action == GLFW_RELEASE)
            std::cout << glfwGetKeyName(key,scancode) << " is released";
        if (mods&GLFW_MOD_SHIFT)
            std::cout<<" with SHIFT";
        if (mods&GLFW_MOD_CONTROL)
            std::cout<<" with CONTROL";
        if (mods&GLFW_MOD_ALT)
            std::cout<<" with ALT";
        std::cout<<std::endl;
    }
}