#ifndef CONTROLLABLE_HPP
#define CONTROLLABLE_HPP

#include <GLFW/glfw3.h>

class Controllable {
public:
	~Controllable() = default;
	virtual void recieveInput(GLFWwindow* window) = 0;
};





#endif