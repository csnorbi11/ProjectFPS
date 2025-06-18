#ifndef WINDOWHANDLER_HPP
#define WINDOWHANDLER_HPP
#include <cstdint>
#include <functional>

#include "Camera.hpp"
#include "Input.hpp"
#include <memory>

enum class WindowType {
    GLFW
};

class InputHandler;

/**
 * @class WindowHandler
 * @brief Abstract base class for handling window operations and input.
 */
class WindowHandler {
public:
    WindowHandler();
    virtual ~WindowHandler();

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



    float getAspectRatio();



    virtual void update();


    bool lockCursor=false;

protected:
    int width=800, height=600;
    float aspectRatio;


	std::unique_ptr<InputHandler> inputHandler;



};

#endif //WINDOWHANDLER_HPP
