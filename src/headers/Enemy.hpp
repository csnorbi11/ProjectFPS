#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "GameObject.hpp"


class Enemy final : public GameObject {
public: 
	Enemy();
	~Enemy() override;

	void update(float deltaTime) override;

};



#endif