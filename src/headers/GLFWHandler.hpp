#ifndef GLFWHANDLER_HPP
#define GLFWHANDLER_HPP

#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowHandler.hpp"

class Camera;
/**
 * @struct GLFWDestroyer
 * @brief Custom deleter for GLFWwindow used with std::unique_ptr.
*/
struct GLFWDestroyer {
    void operator()(GLFWwindow *window) const {
        if (window != nullptr) {
            glfwDestroyWindow(window);
        }
    }
};

/**
* @class GLFWHandler
* @brief Concrete implementation of WindowHandler using GLFW.
*/
class GLFWHandler final : public WindowHandler {
public:

    void debugKeys(int key, int scancode, int action, int mods);
    void debugCursor(double xPos, double yPos);
    void debugMouseButton(int button, int action, int mods);
    void debugMouseScroll(double xOffset, double yOffset);




    GLFWHandler(int width, int height);
    ~GLFWHandler() override;

    bool shouldClose() override;
    void swapBuffers() override;
    void pollEvents() override;
    void closeWindow() override;

private:
    void framebufferSizeCallback(GLFWwindow* window, int width, int height);
    void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

    static std::unique_ptr<GLFWwindow, GLFWDestroyer> window;
};

#endif //WINDOWHANDLER_HPP
