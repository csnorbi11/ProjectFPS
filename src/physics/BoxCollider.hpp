#ifndef AABB_HPP
#define AABB_HPP

#include <glm/glm.hpp>

#include "ICollide.hpp"

class BoxCollider : public ICollide{
public: 
	BoxCollider() = default;
	~BoxCollider() = default;

	bool collide(const BSPTree& other) override;
	bool collide(const BoxCollider& other) override;


private:
	glm::vec3 dimension;
	glm::vec3 offset;
};

#endif