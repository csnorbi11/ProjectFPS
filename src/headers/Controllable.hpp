#ifndef CONTROLLABLE_HPP
#define CONTROLLABLE_HPP

class InputHandler;

struct Controllable {
	~Controllable() = default;
	virtual void recieveInput(const InputHandler& inputHandler) = 0;
};





#endif