#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <glm/glm.hpp>
#include <string>


class GameObject {
public:
    GameObject(const std::string &modelPath,
               glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f));
    GameObject(glm::vec3 position = glm::vec3(0.f), glm::vec3 rotation = glm::vec3(0.f));

    virtual ~GameObject()=default;

    virtual void update(float deltaTime);


    const std::string& getModelPath() const;
    glm::mat4 getModelMatrix() const;

    glm::vec3 position{};
    glm::vec3 rotation{};

protected:
    glm::mat4 transformMatrix{};
    glm::vec3 direction{};

    glm::vec3 front{};
    glm::vec3 right{};
    glm::vec3 up{};

    std::string model{};
};


#endif //GAMEOBJECT_HPP
