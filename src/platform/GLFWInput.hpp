#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include <unordered_map>



using GLFW_KEY = uint8_t;
using GLFW_MOUSE_BUTTON = uint8_t;
using GLFW_ACTION = uint8_t;

class GLFWInput {
public:
	GLFWInput(GLFWwindow* window);
	~GLFWInput();

	void update();

    bool toggleKey(GLFW_KEY key);
    GLFW_ACTION getPrevKeyState(GLFW_KEY key);
    double getMouseScrollY();
    double getMouseX();
    double getMouseY();

    void resetMouseScroll();

private:
    std::unordered_map<GLFW_KEY, GLFW_ACTION> keysPrevStates = {};
    double mouseScrollY = 0.f;
    double mousePosX = 0.f, mousePosY = 0.f;

	GLFWwindow* window = nullptr;

};


#endif