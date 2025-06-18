#ifndef CONTROLLABLE_HPP
#define CONTROLLABLE_HPP

class GLFWInput;

struct Controllable {
	~Controllable() = default;
	virtual void recieveInput(GLFWInput& inputHandler) = 0;
};





#endif