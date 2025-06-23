#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Character.hpp"


class NPC final : public Character {
public: 
	NPC();
	~NPC() override;

	void update(float deltaTime) override;

};



#endif