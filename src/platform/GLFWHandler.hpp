#ifndef GLFWHANDLER_HPP
#define GLFWHANDLER_HPP

#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


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
class GLFWHandler final {
public:
    GLFWHandler(int width=1280, int height=720);
    ~GLFWHandler();

    bool shouldClose();
    void swapBuffers();
    void pollEvents();
    void closeWindow();

    float getAspectRatio();
    GLFWwindow* getWindow() const;

    bool lockCursor = false;

private:
    void framebufferResize(int width, int height);
    void scrollCallback(GLFWwindow* window, double xOffset, double yOffset);

    static std::unique_ptr<GLFWwindow, GLFWDestroyer> window;

    int width, height;
    float aspectRatio;
};

#endif //WINDOWHANDLER_HPP
