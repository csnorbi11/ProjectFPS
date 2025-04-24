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



const std::string& GameObject::getModelPath() const {
    return model;
}
