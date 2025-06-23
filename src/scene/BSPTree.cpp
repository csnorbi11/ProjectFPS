#include "BSPTree.hpp"
#include "../graphics/Renderer.hpp"




BSPTree::BSPTree(std::vector<std::unique_ptr<StaticObject>>& objects, Renderer* renderer)
{
	for (auto& object : objects) {
		if (object!=nullptr) {
			Model* model = renderer->getModels()[object->getModelPath()].get();
			for (auto& mesh : model->getMeshes()) {
				for (auto& triangle : mesh->getTriangles()) {
					triangles.push_back(triangle);
				}
			}
		}
	}

	buildTree();
}

void BSPTree::buildTree()
{
	for (auto& tri : triangles) {
		printf("Triangle vertices: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n",
			tri.vertices[0].x, tri.vertices[0].y, tri.vertices[0].z,
			tri.vertices[1].x, tri.vertices[1].y, tri.vertices[1].z,
			tri.vertices[2].x, tri.vertices[2].y, tri.vertices[2].z);
	}
}

void BSPTree::buildNode(std::unique_ptr<BSPNode>& node)
{
	//StaticObject* object = objects[currentObjIndex].get();
	//if (object == nullptr) {
	//	return;
	//}
	//node = std::make_unique<BSPNode>();
	//node->objects.push_back(object);
	//for (auto& obj : objects) {
	//	if (obj.get() == object) {
	//		continue;
	//	}

	//}
}

