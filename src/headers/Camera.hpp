#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "GameObject.hpp"


class Camera final :public GameObject {
public:
    Camera();
    ~Camera() override=default;

    void update(float deltaTime) override;

    glm::mat4 getViewMatrix();

private:
    void updateCameraVectors();

    float prevMousePosX, prevMousePosY;
    float mouseSensitivity;
};

#endif //CAMERA_HPP
