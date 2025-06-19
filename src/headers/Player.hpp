#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "GameObject.hpp"
#include "Controllable.hpp"


class Camera;

class Player final : public GameObject, public Controllable {
public:
	Player();
	~Player() override;

	void update(float deltaTime) override;
	void recieveInput(GLFWwindow* window) override;


private:
	Camera* camera = nullptr;

};


#endif