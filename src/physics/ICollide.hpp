#ifndef COLLIDE_HPP
#define COLLIDE_HPP

class BSPTree;
class BoxCollider;

class ICollide {
public:
	virtual ~ICollide() = default;
	virtual bool collide(const ICollide& other) = 0;

	virtual bool collide(const BSPTree& other) = 0;
	virtual bool collide(const BoxCollider& other) = 0;
};

#endif