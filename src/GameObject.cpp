#include "headers/GameObject.hpp"
#include "headers/ShaderProgram.hpp"

GameObject::GameObject(const std::string &modelPath, const glm::vec3 position, const glm::vec3 rotation)
    : position(position),
      rotation(rotation),
      model(modelPath) {
}

GameObject::~GameObject() {
}

const std::string& GameObject::getModelPath() const {
    return model;
}

const glm::mat4 GameObject::getModelMatrix() const {
    return transformMatrix;
}
