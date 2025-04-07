#include "headers/GLFWHandler.hpp"

#include <iostream>
#include <memory>
#include <ostream>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

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
    glfwSetFramebufferSizeCallback(window.get(), framebuffer_size_callback);

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

float GLFWHandler::getlElapsedTime() {
    return glfwGetTime();
}


void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

bool GLFWHandler::InputHandler::onKeyboard(int key) {
    if (glfwGetKey(window.get(),key)==GLFW_PRESS)
        return true;
    return false;
}

bool GLFWHandler::InputHandler::onMousePressed(int but, int pX, int pY) {
    if (glfwGetMouseButton(window.get(),but)==GLFW_PRESS)
        return true;
    return false;
}

void GLFWHandler::InputHandler::onMouseMotion(int pX, int pY) {
}
