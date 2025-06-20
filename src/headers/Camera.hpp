#ifndef CAMERA_HPP
#define CAMERA_HPP

#include "DynamicObject.hpp"
#include "IControllable.hpp"

class Player;


class Camera final :public DynamicObject, public IControllable {
public:
    Camera();
    ~Camera() override;

    void update(float deltaTime) override;
    void recieveInput(GLFWwindow* window) override;

    glm::mat4 getViewMatrix() const;

private:
	Player* player = nullptr;

    float prevMousePosX=0, prevMousePosY = 0;
    float mouseSensitivity=1.f;
    float offsetX, offsetY;

    float yaw=0.f, pitch=0.f;
};

#endif //CAMERA_HPP
