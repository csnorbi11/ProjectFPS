#include "headers/WindowHandler.hpp"
#include "headers/InputHandler.hpp"


WindowHandler::WindowHandler()
    :
    aspectRatio(static_cast<float>(width) / static_cast<float>(height))
{
	inputHandler = std::make_unique<InputHandler>();
}
WindowHandler::~WindowHandler()=default;



float WindowHandler::getAspectRatio() {
    return aspectRatio;
}





void WindowHandler::update() {
    inputHandler->toggleKey(Input::Key::LEFT);
}


