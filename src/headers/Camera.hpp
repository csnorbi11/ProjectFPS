#ifndef CAMERA_HPP
#define CAMERA_HPP
#include "GameObject.hpp"
#include "Controllable.hpp"


class Camera final :public GameObject, public Controllable {
public:
    Camera();
    ~Camera() override;

    void update(float deltaTime) override;
    void recieveInput(const InputHandler& inputHandler) override;

    glm::mat4 getViewMatrix() const;

private:
    void updateCameraVectors();

    float prevMousePosX=0, prevMousePosY=0;
    float mouseSensitivity=1.f;
};

#endif //CAMERA_HPP
