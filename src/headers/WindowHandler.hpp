#ifndef WINDOWHANDLER_HPP
#define WINDOWHANDLER_HPP
#include <cstdint>
#include <functional>

#include "Camera.hpp"
#include "Input.hpp"

enum class WindowType {
    GLFW
};


/**
 * @class WindowHandler
 * @brief Abstract base class for handling window operations and input.
 */
class WindowHandler {
public:
    WindowHandler(const int width, const int height);
    virtual ~WindowHandler() = default;

    /**
     * @brief Checks if the window should close.
     * @return True if the window is set to close, false otherwise.
     */
    virtual bool shouldClose() = 0;

    /**
     * @brief Swaps the front and back buffers of the window.
     *
     * Typically used at the end of a frame to present the rendered image.
     */
    virtual void swapBuffers() = 0;

    /**
     * @brief Polls for and processes input events.
     *
     * Should be called each frame to keep input and window events updated.
     */
    virtual void pollEvents() = 0;

    /**
     * @brief Forces the window to close.
     */
    virtual void closeWindow() = 0;

    static Input::Action getKeyState(Input::Key key);
    static Input::Action getMouseButtonState(uint8_t button);
    static double getMouseScrollX();
    static double getMouseScrollY();
    static double getMouseX();
    static double getMouseY();
    static double getCursorOffsetX();
    static double getCursorOffsetY();
    static void resetMouseScroll();

    void setActiveCamera(Camera* camera);

protected:
    int width, height;
    float aspectRatio;

    /// Map of key states (pressed/released/held).
    static std::unordered_map<Input::Key, Input::Action> keys;
    /// Map of mouse button states (pressed/released/held).
    static std::unordered_map<uint8_t, Input::Action> mouseButtons;
    static double mouseScrollX, mouseScrollY;
    static double mousePosX, mousePosY;
    static double cursorPrevOffsetX, cursorPrevOffsetY;

};

#endif //WINDOWHANDLER_HPP
