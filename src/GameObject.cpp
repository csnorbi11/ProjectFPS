#include "headers/GameObject.hpp"
#include "headers/ShaderProgram.hpp"

GameObject::GameObject(const std::string &modelPath, const glm::vec3 position, const glm::vec3 rotation)
    :
        position(position),
        rotation(rotation),
        direction(0.f,0.f,-1.f),
        front(0.f,0.f,-1.f),
        right(1.f,0.f,0.f),
        up(0.f,1.f,0.f),
        model(modelPath)
{}

GameObject::GameObject(glm::vec3 position, glm::vec3 rotation)
    :
        position(position),
        rotation(rotation),
        direction(0.f,0.f,-1.f),
        front(0.f,0.f,-1.f),
        right(1.f,0.f,0.f),
        up(0.f,1.f,0.f)
{}

void GameObject::update(float deltaTime) {



}



const std::string& GameObject::getModelPath() const {
    return model;
}
