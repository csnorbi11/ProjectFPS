#ifndef BSPTREE_HPP
#define BSPTREE_HPP

#include <memory>
#include <vector>

#include "BSPNode.hpp"
#include "StaticObject.hpp"
#include "../graphics/Mesh.hpp"

class Renderer;

class BSPTree {
public:
	BSPTree(std::vector<std::unique_ptr<StaticObject>>& objects, Renderer* renderer);
	~BSPTree() = default;

	


private:
	void buildTree();

	void buildNode(std::unique_ptr<BSPNode>& node);

	std::unique_ptr<BSPNode> root;
	std::vector<Triangle> triangles;

	size_t currentObjIndex = 0;
};



#endif