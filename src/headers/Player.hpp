#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <memory>

#include "GameObject.hpp"
#include "IControllable.hpp"
#include "ICollide.hpp"



class Camera;


class Player final : public GameObject, public IControllable {
public:
	Player();
	~Player() override;

	void update(float deltaTime) override;
	void recieveInput(GLFWwindow* window) override;


private:
	Camera* camera = nullptr;

	

};


#endif