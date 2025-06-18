#ifndef CONTROLLABLE_HPP
#define CONTROLLABLE_HPP

#include "Input.hpp"


class Controllable {
public:
	~Controllable() = default;
	virtual void recieveInput(Input::IInput& input) = 0;
};





#endif