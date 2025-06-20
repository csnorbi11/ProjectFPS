#ifndef CHARACTER_HPP
#define CHARACTER_HPP

#include "DynamicObject.hpp"

class Character : public DynamicObject {
public:
	Character() = default;
	~Character() override = default;
};

#endif