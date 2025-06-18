#include "headers/GLFWFactory.hpp"
#include "headers/GLFWHandler.hpp"
#include "headers/GLFWInput.hpp"

GLFWFactory::GLFWFactory() = default;
GLFWFactory::~GLFWFactory() = default;

WindowHandler* GLFWFactory::createWindowHandler()
{
	return new GLFWHandler(1280, 720);
}

Input::IInput* GLFWFactory::createInputHandler(WindowHandler* windowHandler)
{
	return new GLFWInput(*dynamic_cast<GLFWInput*>(windowHandler));
}

