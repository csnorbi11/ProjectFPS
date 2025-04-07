#ifndef WINDOWHANDLER_HPP
#define WINDOWHANDLER_HPP
#include <cstdint>
#include <functional>
#include <GLFW/glfw3.h>

enum class WindowType {
    GLFW
};

class WindowHandler {
public:
    WindowHandler(const int width, const int height)
        : width(width),
          height(height),
          aspectRatio(
              static_cast<float>(width) / static_cast<float>(height)
          ) {
    }

    virtual ~WindowHandler() = default;

    virtual bool shouldClose() =0;

    virtual void swapBuffers() =0;

    virtual void pollEvents() =0;

    virtual void closeWindow() =0;

    static uint8_t getKeyState(uint16_t key);

    static uint8_t getMouseButtonState(uint8_t button);

    static double getMouseScrollx();

    static double getMouseScrolly();

    static double getMouseX();

    static double getMouseY();

    static void resetMouseScroll();

protected:
    int width, height;
    float aspectRatio;


    static std::unordered_map<uint16_t, uint8_t> keys;
    static std::unordered_map<uint8_t, uint8_t> mouseButtons;
    static double mouseScrollx, mouseScrolly;
    static double mousePosx, mousePosy;
};

#endif //WINDOWHANDLER_HPP
