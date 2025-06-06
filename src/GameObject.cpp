#include "headers/GameObject.hpp"
#include "headers/ShaderProgram.hpp"

GameObject::GameObject(GameObjectParams params)
    :
        position(params.position),
        rotation(params.rotation),
        direction(0.f,0.f,-1.f),
        front(0.f,0.f,-1.f),
        right(1.f,0.f,0.f),
        up(0.f,1.f,0.f),
        model(params.modelPath)
{}


void GameObject::update(float deltaTime) {



}

void GameObject::rotate(const glm::vec3& axis, float angle)
{
	glm::vec3 normalizedAxis = glm::normalize(axis);
	glm::quat rotationQuat = glm::angleAxis(angle, normalizedAxis);
	rotation = glm::normalize(rotationQuat * rotation);

	front = rotation * glm::vec3(0.f, 0.f, -1.f);
	up = rotation * glm::vec3(0.f, 1.f, 0.f);
	right = rotation * glm::vec3(1.f, 0.f, 0.f);
}

void GameObject::rotateGlobal(const glm::vec3& axis, float angle)
{
	glm::vec3 normalizedAxis = glm::normalize(axis);
	glm::quat rotationQuat = glm::angleAxis(angle, normalizedAxis);
	rotation = glm::normalize(rotation*rotationQuat);

	front = rotation * glm::vec3(0.f, 0.f, -1.f);
	up = rotation * glm::vec3(0.f, 1.f, 0.f);
	right = rotation * glm::vec3(1.f, 0.f, 0.f);
}

void GameObject::rotateEuler(const glm::vec3& eulerAngles)
{
	glm::quat qx = glm::angleAxis(eulerAngles.x, glm::vec3(1.f, 0.f, 0.f));
	glm::quat qy = glm::angleAxis(eulerAngles.y, glm::vec3(0.f, 1.f, 0.f));
	glm::quat qz = glm::angleAxis(eulerAngles.z, glm::vec3(0.f, 0.f, 1.f));

	rotation = glm::normalize(qz * qy * qx*rotation);
}

void GameObject::rotateEulerX(float angle)
{
	rotateGlobal(glm::vec3(1.f, 0.f, 0.f),angle);
}

void GameObject::rotateEulerY(float angle)
{
	rotate(glm::vec3(0.f, 1.f, 0.f), angle);
}

void GameObject::rotateEulerZ(float angle)
{
	rotate(glm::vec3(0.f, 0.f, 1.f), angle);
}

glm::vec3 GameObject::getEulerAngles() const
{
	return glm::eulerAngles(rotation);
}

glm::quat GameObject::getQuaternion() const
{
	return rotation;
}



const std::string& GameObject::getModelPath() const {
    return model;
}
