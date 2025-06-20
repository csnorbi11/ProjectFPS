#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include "Character.hpp"
#include "IControllable.hpp"


class Player final : public Character, public IControllable {
public:
	Player();
	~Player() override;

	void update(float deltaTime) override;
	void recieveInput(GLFWwindow* window) override;


};


#endif