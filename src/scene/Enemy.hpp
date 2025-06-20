#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Character.hpp"


class Enemy final : public Character {
public: 
	Enemy();
	~Enemy() override;

	void update(float deltaTime) override;

};



#endif