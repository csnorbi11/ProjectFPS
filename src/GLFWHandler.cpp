#include "headers/GLFWHandler.hpp"

#include <iostream>
#include <memory>
#include <ostream>


#include "headers/DebugMode.hpp"
#include "headers/Game.hpp"
#include "headers/GLFWInput.hpp"


std::unique_ptr<GLFWwindow, GLFWDestroyer> GLFWHandler::window = nullptr;


GLFWHandler::GLFWHandler(int width, int height)
    :
	width(width),
    height(height),
    aspectRatio(static_cast<float>(width) / static_cast<float>(height)),
    lockCursor(false)
{
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
	glfwSetWindowUserPointer(window.get(), this);

    glfwSetFramebufferSizeCallback(window.get(), [](GLFWwindow* win, int w, int h) {
        auto* self = static_cast<GLFWHandler*>(glfwGetWindowUserPointer(win));
        if (self) self->framebufferResize(w, h);
        });

    //glfwSetScrollCallback(window.get(), InputHandler::scrollCallback);

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
    glfwSwapBuffers(window.get());
}

void GLFWHandler::pollEvents() {
    if (lockCursor) {
        glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    }
    else {
        glfwSetInputMode(window.get(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }

	

    glfwPollEvents();
    
}

void GLFWHandler::closeWindow() {
    glfwSetWindowShouldClose(window.get(), GLFW_TRUE);
}

float GLFWHandler::getAspectRatio()
{
    return aspectRatio;
}

GLFWwindow* GLFWHandler::getWindow() const
{
    return window.get();
}


void GLFWHandler::scrollCallback(GLFWwindow *window, const double xOffset, const double yOffset) {
    //mouseScrollX = xOffset;
    //mouseScrollY = yOffset;
}

void GLFWHandler::framebufferResize(int width, int height) {
    glViewport(0, 0, width, height);
    this->width = width;
    this->height = height;
    aspectRatio = static_cast<float>(width) / static_cast<float>(height);
}
