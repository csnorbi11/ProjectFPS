#ifndef STATICOBJECT_HPP
#define STATICOBJECT_HPP


#include <memory>

#include "GameObject.hpp"


class StaticObject final : public GameObject {
public:
	StaticObject();
	~StaticObject() override;

	void update(float deltaTime) override;

};

#endif