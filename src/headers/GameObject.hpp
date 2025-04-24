#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <glm/glm.hpp>
#include <string>

struct GameObjectParams {
    const std::string modelPath="";
    glm::vec3 position{0.f};
    glm::vec3 rotation{0.f};
};

class GameObject {
public:
    explicit GameObject(GameObjectParams params);

    virtual ~GameObject()=default;

    virtual void update(float deltaTime);


    const std::string& getModelPath() const;

    glm::vec3 position={};
    glm::vec3 rotation={};

protected:
    glm::vec3 direction;

    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    std::string model{};
};


#endif //GAMEOBJECT_HPP
