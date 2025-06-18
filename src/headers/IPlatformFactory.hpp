#ifndef IPLATFORMFACTORY_HPP
#define IPLATFORMFACTORY_HPP

#include "Input.hpp"

class WindowHandler;


class IPlatformFactory {
public:
	virtual ~IPlatformFactory() = default;

	virtual WindowHandler* createWindowHandler() = 0;
	virtual Input::IInput* createInputHandler(WindowHandler* windowHandler) = 0;
};

#endif