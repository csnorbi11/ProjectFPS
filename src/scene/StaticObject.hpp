#ifndef STATICOBJECT_HPP
#define STATICOBJECT_HPP


#include <memory>

#include "GameObject.hpp"


class StaticObject final : public GameObject {
public:
	StaticObject(GameObjectParams goParams);
	~StaticObject() override;

	void update(float deltaTime) override;

};

#endif