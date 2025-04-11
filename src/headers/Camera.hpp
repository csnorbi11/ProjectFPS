#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "GameObject.hpp"


class Camera final :public GameObject {
public:
    Camera();
    ~Camera() override=default;

    void update(float deltaTime) override;

    void processCursorOffset(double offsetX, double offsetY);

    glm::mat4 getViewMatrix();

private:
    void updateCameraVectors();

    float mouseSensitivity;
};

#endif //CAMERA_HPP
