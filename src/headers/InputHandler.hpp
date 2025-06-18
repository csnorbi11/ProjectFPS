#ifndef INPUTHANDLER_HPP
#define INPUTHANDLER_HPP

#include "Input.hpp"
#include <unordered_map>

class InputHandler {
public:
	InputHandler() = default;
	~InputHandler() = default;

    bool toggleKey(Input::Key key);
    Input::Action getKeyState(Input::Key key);
    Input::Action getKeyPrevState(Input::Key key);
    Input::Action getMouseButtonState(uint8_t button);
    double getMouseScrollX();
    double getMouseScrollY();
    double getMouseX();
    double getMouseY();
    void resetMouseScroll();

private:
    /// Map of key states (pressed/released/held).
    std::unordered_map<Input::Key, Input::Action> keys = {};
    std::unordered_map<Input::Key, Input::Action> keysPrevStates = {};
    /// Map of mouse button states (pressed/released/held).
    std::unordered_map<uint8_t, Input::Action> mouseButtons = {};
    double mouseScrollX = 0.f, mouseScrollY = 0.f;
    double mousePosX = 0.f, mousePosY = 0.f;

};


#endif