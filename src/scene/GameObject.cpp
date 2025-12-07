#include "GameObject.hpp"

GameObject::GameObject() = default;

GameObject::GameObject(const GameObjectParams& params)
    :
        position(params.position),
        orientation(params.rotation),
        direction(0.f,0.f,-1.f),
        forward(0.f,0.f,-1.f),
        right(1.f,0.f,0.f),
        up(0.f,1.f,0.f),
        model(params.model)
{}


GameObject::~GameObject() = default;

void GameObject::update(float deltaTime) {

}

void GameObject::rotateLocal(const glm::vec3& axis, float angle)
{
	glm::vec3 normalizedAxis = glm::normalize(axis);
	glm::quat rotationQuat = glm::angleAxis(angle, normalizedAxis);
	orientation = glm::normalize(rotationQuat * orientation);

	calculateVectors();
}

void GameObject::rotateGlobal(const glm::vec3& axis, float angle)
{
	glm::vec3 normalizedAxis = glm::normalize(axis);
	glm::quat rotationQuat = glm::angleAxis(angle, normalizedAxis);
	orientation = glm::normalize(orientation*rotationQuat);

	calculateVectors();
}

void GameObject::calculateVectors()
{
	forward = orientation * glm::vec3(0.f, 0.f, -1.f);
	up = orientation * glm::vec3(0.f, 1.f, 0.f);
	right = orientation * glm::vec3(1.f, 0.f, 0.f);
}

void GameObject::rotateEuler(const glm::vec3& eulerAngles, bool isGlobal)
{
	glm::quat qx = glm::angleAxis(eulerAngles.x, glm::vec3(1.f, 0.f, 0.f));
	glm::quat qy = glm::angleAxis(eulerAngles.y, glm::vec3(0.f, 1.f, 0.f));
	glm::quat qz = glm::angleAxis(eulerAngles.z, glm::vec3(0.f, 0.f, 1.f));

	orientation = isGlobal? glm::normalize(qz * qy * qx*orientation): glm::normalize(orientation* qz * qy * qx);

	calculateVectors();
}

void GameObject::rotateEulerX(float angle, bool isGlobal)
{
	if (isGlobal)
		rotateGlobal(glm::vec3(1.f, 0.f, 0.f), angle);
	else
		rotateLocal(glm::vec3(1.f, 0.f, 0.f),angle);
}

void GameObject::rotateEulerY(float angle, bool isGlobal)
{
	if (isGlobal)
		rotateGlobal(glm::vec3(0.f, 1.f, 0.f), angle);
	else
		rotateLocal(glm::vec3(0.f, 1.f, 0.f), angle);
}

void GameObject::rotateEulerZ(float angle, bool isGlobal)
{
	if (isGlobal)
		rotateGlobal(glm::vec3(0.f, 0.f, 1.f), angle);
	else
		rotateLocal(glm::vec3(0.f, 0.f, 1.f), angle);
}

glm::vec3 GameObject::getEulerAngles() const
{
	return glm::eulerAngles(orientation);
}

glm::quat GameObject::getQuaternion() const
{
	return orientation;
}

void GameObject::setQuaternion(const glm::quat& q)
{
	orientation = q;
	calculateVectors();
}

void GameObject::setModel(Model* model)
{
	this->model = model;
}



Model* GameObject::getModel() const {
    return model;
}
