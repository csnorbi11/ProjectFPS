#ifndef GLFWHANDLER_HPP
#define GLFWHANDLER_HPP

#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowHandler.hpp"

/**
 * @struct GLFWDestroyer
 * @brief Custom deleter for GLFWwindow used with std::unique_ptr.
*/
struct GLFWDestroyer {
    void operator()(GLFWwindow *window) const {
        if (window != nullptr) {
            glfwDestroyWindow(window);
            glfwTerminate();
        }
    }
};

/**
* @class GLFWHandler
* @brief Concrete implementation of WindowHandler using GLFW.
*/
class GLFWHandler final : public WindowHandler {
public:
    struct InputHandler {
        static void framebufferSizeCallback(GLFWwindow *window, int width, int height);
        static void keyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void cursorPositionCallback(GLFWwindow *window, double xPos, double yPos);
        static void mouseButtonCallback(GLFWwindow *window, int button, int action, int mods);
        static void scrollCallback(GLFWwindow *window, double xOffset, double yOffset);

        static void debugKeys(int key, int scancode, int action, int mods);
        static void debugCursor(double xPos, double yPos);
        static void debugMouseButton(int button, int action, int mods);
        static void debugMouseScroll(double xOffset, double yOffset);
    };

    GLFWHandler();
    ~GLFWHandler() override = default;

    bool shouldClose() override;
    void swapBuffers() override;
    void pollEvents() override;
    void closeWindow() override;

private:
    static std::unique_ptr<GLFWwindow, GLFWDestroyer> window;
};

#endif //WINDOWHANDLER_HPP
