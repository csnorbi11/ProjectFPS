#ifndef GLFWHANDLER_HPP
#define GLFWHANDLER_HPP

#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "WindowHandler.hpp"

struct GLFWDestroyer{
    void operator()(GLFWwindow* window) const {
      if(window!=nullptr){
          glfwDestroyWindow(window);
          glfwTerminate();
      }
    }
};


class GLFWHandler final : public WindowHandler {
public:
    GLFWHandler();
    ~GLFWHandler() override =default;

    bool shouldClose() override;
    void swapBuffers() override;
    void pollEvents() override;
    float getlElapsedTime() override;

    struct InputHandler {
        static bool onKeyboard(int key);
        static bool onMousePressed(int but, int pX, int pY);
        static void onMouseMotion(int pX, int pY);
    };

private:
    static std::unique_ptr<GLFWwindow, GLFWDestroyer> window;

};

#endif //WINDOWHANDLER_HPP
