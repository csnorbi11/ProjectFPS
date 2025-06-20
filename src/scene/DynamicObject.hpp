#ifndef DYNAMICOBJECT_HPP
#define DYNAMICOBJECT_HPP

#include "GameObject.hpp"

class DynamicObject : public GameObject {
public:
	DynamicObject()=default;
	~DynamicObject() override = default;
};

#endif