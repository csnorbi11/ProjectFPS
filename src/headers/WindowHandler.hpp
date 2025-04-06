#ifndef WINDOWHANDLER_HPP
#define WINDOWHANDLER_HPP

enum class WindowType {
    GLFW
};

class WindowHandler{
public:
    WindowHandler(uint32_t width, uint32_t height)
        :
    width(width),
    height(height)
    {}

    virtual ~WindowHandler()=default;

    virtual bool shouldClose()=0;
    virtual void swapBuffers()=0;
    virtual void pollEvents()=0;
    virtual float getlElapsedTime()=0;

protected:
    uint32_t width, height;
};

#endif //WINDOWHANDLER_HPP
