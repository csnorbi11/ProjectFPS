#ifndef WINDOWHANDLER_HPP
#define WINDOWHANDLER_HPP

enum class WindowType {
    GLFW
};

class WindowHandler{
public:
    WindowHandler(const uint32_t width, const uint32_t height)
        :
    width(width),
    height(height),
    aspectRatio(
        static_cast<float>(width)/static_cast<float>(height)
        )
    {}

    virtual ~WindowHandler()=default;

    virtual bool shouldClose()=0;
    virtual void swapBuffers()=0;
    virtual void pollEvents()=0;
    virtual float getElapsedTime()=0;

    static const std::unordered_map<uint16_t,bool>& getKeys() {
        return keys;
    }

protected:
    uint32_t width, height;
    float aspectRatio;

    static std::unordered_map<uint16_t, bool> keys;
};

#endif //WINDOWHANDLER_HPP
