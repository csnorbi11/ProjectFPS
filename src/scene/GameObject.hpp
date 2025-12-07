#ifndef GAMEOBJECT_HPP
#define GAMEOBJECT_HPP

#include <glm/glm.hpp>
#include <string>
#include "graphics/Model.hpp"

struct GameObjectParams {
    Model const* model=nullptr;
    glm::vec3 position{0.f};
    glm::vec3 rotation{0.f};
};

class GameObject {
public:

    GameObject() = default;
    explicit GameObject(GameObjectParams params);
    virtual ~GameObject()=default;

    virtual void update(float deltaTime)=0;

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

    bool isDrawable() const;
    Model const& getModel() const;

    glm::vec3 position = { 0,0,0 };
    glm::quat orientation = {};

protected:
    glm::vec3 direction = { 0,0,1 };

    glm::vec3 forward = { 0,0,1 };
    glm::vec3 right = { 1,0,0 };
    glm::vec3 up = { 0,1,0 };

    Model const* model=nullptr;
    bool drawable = false;

};


#endif //GAMEOBJECT_HPP
