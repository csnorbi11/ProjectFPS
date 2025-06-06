#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <glm/glm.hpp>
#include <string>
#include <glm/gtc/quaternion.hpp>

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

    void rotate(const glm::vec3& axis, float angle);    
    void rotateGlobal(const glm::vec3& axis, float angle);    
	void rotateEuler(const glm::vec3& eulerAngles);
	void rotateEulerX(float angle);
	void rotateEulerY(float angle);
	void rotateEulerZ(float angle);

    glm::vec3 getEulerAngles() const;
	glm::quat getQuaternion() const;

    const std::string& getModelPath() const;

    glm::vec3 position={};
    

protected:
    glm::vec3 direction;

    glm::vec3 front;
    glm::vec3 right;
    glm::vec3 up;

    std::string model{};

private:
    glm::quat rotation = {};
};


#endif //GAMEOBJECT_HPP
