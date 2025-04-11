#include "headers/GameObject.hpp"
#include "headers/ShaderProgram.hpp"

GameObject::GameObject(const std::string &modelPath, const glm::vec3 position, const glm::vec3 rotation)
    :
        transformMatrix(1.f),
        position(position),
        rotation(rotation),
        front(glm::vec3(0.f,0.f,-1.f)),
        right(glm::vec3(1.f,0.f,0.f)),
        up(glm::vec3(0.f,1.f,0.f)),
        model(modelPath)
{
}

GameObject::GameObject(glm::vec3 position, glm::vec3 rotation)
    :
        transformMatrix(1.f),
        position(position),
        rotation(rotation),
        front(glm::vec3(0.f,0.f,-1.f)),
        right(glm::vec3(1.f,0.f,0.f)),
        up(glm::vec3(0.f,1.f,0.f))
{
}

void GameObject::update(float deltaTime) {


    transformMatrix = glm::translate(glm::mat4(1.0f), position);
    transformMatrix = glm::rotate(transformMatrix, rotation.x, glm::vec3(0.0f,1.0f,0.0f));
    transformMatrix = glm::rotate(transformMatrix, rotation.y, glm::vec3(1.0f,0.0f,0.0f));
    transformMatrix = glm::rotate(transformMatrix, rotation.z, glm::vec3(0.0f,0.0f,1.0f));
}



const std::string& GameObject::getModelPath() const {
    return model;
}
glm::mat4 GameObject::getModelMatrix() const {
    return transformMatrix;
}
