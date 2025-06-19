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

    GameObject();
    explicit GameObject(GameObjectParams params);

    virtual ~GameObject()=default;

    virtual void update(float deltaTime);

    void rotateLocal(const glm::vec3& axis, float angle);    
    void rotateGlobal(const glm::vec3& axis, float angle);
    void calculateVectors();
	void rotateEuler(const glm::vec3& eulerAngles, bool isGlobal=false);
	void rotateEulerX(float angle, bool isGlobal = false);
	void rotateEulerY(float angle, bool isGlobal = false);
	void rotateEulerZ(float angle, bool isGlobal = false);

    glm::vec3 getEulerAngles() const;
	glm::quat getQuaternion() const;

    void setQuaternion(const glm::quat& q);

    const std::string& getModelPath() const;

    glm::vec3 position={};
    glm::quat orientation = {};

protected:
    glm::vec3 direction;

    glm::vec3 forward;
    glm::vec3 right;
    glm::vec3 up;

    std::string model{};


};


#endif //GAMEOBJECT_HPP
