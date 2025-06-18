#ifndef GLFWFACTORY_HPP
#define GLFWFACTORY_HPP

#include "IPlatformFactory.hpp"

class GLFWFactory : public IPlatformFactory {
public:
	GLFWFactory();
	~GLFWFactory();

	WindowHandler* createWindowHandler() override;
	Input::IInput* createInputHandler(WindowHandler* windowHandler) override;
};

#endif