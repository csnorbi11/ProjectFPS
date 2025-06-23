#include "BSPTree.hpp"




BSPTree::BSPTree(std::vector<std::unique_ptr<StaticObject>>& objects)
	: 
	objects(objects)
{
	buildTree();
}

void BSPTree::buildTree()
{

}

void BSPTree::buildNode(std::unique_ptr<BSPNode>& node)
{
	StaticObject* object = objects[currentObjIndex].get();
	if (object == nullptr) {
		return;
	}
	node = std::make_unique<BSPNode>();
	node->objects.push_back(object);
	for (auto& obj : objects) {
		if (obj.get() == object) {
			continue;
		}

	}
}

