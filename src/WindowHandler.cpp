#include "headers/WindowHandler.hpp"


WindowHandler::WindowHandler()
    :
    aspectRatio(static_cast<float>(width) / static_cast<float>(height))
{}
WindowHandler::~WindowHandler()=default;

float WindowHandler::getAspectRatio() {
    return aspectRatio;
}
