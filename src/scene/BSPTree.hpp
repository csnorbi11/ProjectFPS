#ifndef BSPTREE_HPP
#define BSPTREE_HPP

#include <memory>

#include "BSPNode.hpp"

class BSPTree {
public:
	BSPTree();
	~BSPTree();


private:
	std::unique_ptr<BSPNode> root;
};



#endif