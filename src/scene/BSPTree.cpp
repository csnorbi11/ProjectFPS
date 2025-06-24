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
	root = std::make_unique<BSPNode>();
	buildTree();
}

void BSPTree::buildTree()
{
	//for (auto& tri : triangles) {
	//	printf("Triangle vertices: (%f, %f, %f), (%f, %f, %f), (%f, %f, %f)\n",
	//		tri.vertices[0].x, tri.vertices[0].y, tri.vertices[0].z,
	//		tri.vertices[1].x, tri.vertices[1].y, tri.vertices[1].z,
	//		tri.vertices[2].x, tri.vertices[2].y, tri.vertices[2].z);
	//}
	buildNode(root);

}

void BSPTree::buildNode(std::unique_ptr<BSPNode>& node)
{
	if (currentObjIndex >= triangles.size()) {
		return;
	}
	if (!node) node = std::make_unique<BSPNode>();
	if (!node->front) node->front = std::make_unique<BSPNode>();
	if (!node->back) node->back = std::make_unique<BSPNode>();
	node->planePoint = triangles[currentObjIndex].vertices[0];
	node->planeNormal = triangles[currentObjIndex].normal;
	currentObjIndex++;
	for (auto& tri : triangles) {
		float d0 = dot(node->planeNormal, (node->planePoint - tri.vertices[0]));
		float d1 = dot(node->planeNormal, (node->planePoint - tri.vertices[1]));
		float d2 = dot(node->planeNormal, (node->planePoint - tri.vertices[2]));
		if (d0 > 0 && d1 > 0 && d2 > 0) {
			node->front->triangles.push_back(&tri);
		}
		else if (d0 < 0 && d1 < 0 && d2 < 0) {
			node->back->triangles.push_back(&tri);
		}
		else if (d0 == 0 && d1 == 0 && d2 == 0) {
			node->triangles.push_back(&tri);
		}
		else {
			
		}
	}
	buildNode(node->front);
	buildNode(node->back);

}

