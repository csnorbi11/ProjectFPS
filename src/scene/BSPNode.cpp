#include "BSPNode.hpp"

BSPNode::BSPNode()
{
	front = std::unique_ptr<BSPNode>();
	back = std::unique_ptr<BSPNode>();
}
