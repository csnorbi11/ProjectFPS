#ifndef BSPTREE_HPP
#define BSPTREE_HPP

#include <memory>
#include <vector>

#include "BSPNode.hpp"
#include "StaticObject.hpp"

class BSPTree {
public:
	BSPTree(std::vector<std::unique_ptr<StaticObject>>& objects);
	~BSPTree() = default;

	


private:
	void buildTree();

	void buildNode(std::unique_ptr<BSPNode>& node);

	std::unique_ptr<BSPNode> root;
	std::vector<std::unique_ptr<StaticObject>>& objects;

	size_t currentObjIndex = 0;
};



#endif