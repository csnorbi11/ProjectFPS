#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "GameObject.hpp"


class Camera final :public GameObject {
public:
    Camera();
    ~Camera() override;

    void update(float deltaTime) override;

    glm::mat4 getViewMatrix() const;

private:

    float prevMousePosX=0, prevMousePosY = 0;
    float mouseSensitivity=1.f;

    float yaw=0.f, pitch=0.f;
};

#endif //CAMERA_HPP
