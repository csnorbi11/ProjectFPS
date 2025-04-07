#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <glm/glm.hpp>
#include <string>


class GameObject {
public:
    GameObject(const std::string &modelPath,
               glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f));

    ~GameObject();

    const std::string& getModelPath() const;

    const glm::mat4 getModelMatrix() const;

protected:
    glm::mat4 transformMatrix{};
    glm::vec3 position{};
    glm::vec3 rotation{};
    std::string model{};
};


#endif //GAMEOBJECT_HPP
