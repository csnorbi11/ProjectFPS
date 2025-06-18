#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include "Input.hpp"
#include <unordered_map>

class GLFWInput : public Input::IInput {
public:
	GLFWInput(GLFWwindow* window);
	~GLFWInput();

	void update() override;

    bool toggleKey(Input::Key key) override;
    Input::Action getKeyState(Input::Key key) override;
    Input::Action getMouseButtonState(uint8_t button) override;
    double getMouseScrollY() override;
    double getMouseX() override;
    double getMouseY() override;

    void resetMouseScroll();

private:
    /// Map of key states (pressed/released/held).
    std::unordered_map<Input::Key, Input::Action> keys = {};
    std::unordered_map<Input::Key, Input::Action> keysPrevStates = {};
    /// Map of mouse button states (pressed/released/held).
    std::unordered_map<uint8_t, Input::Action> mouseButtons = {};
    double mouseScrollY = 0.f;
    double mousePosX = 0.f, mousePosY = 0.f;

	GLFWwindow* window = nullptr;

};


#endif