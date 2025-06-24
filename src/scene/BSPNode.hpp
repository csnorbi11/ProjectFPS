#ifndef BSPNODE_HPP
#define BSPNODE_HPP
#include <glm/vec3.hpp>
#include <memory>
#include <vector>

#include "../graphics/Mesh.hpp"

struct BSPNode {
	glm::vec3 planePoint;
	glm::vec3 planeNormal;
	std::vector<Triangle*> triangles;

  std::unique_ptr<BSPNode> front, back;
};

#endif //BSPNODE_HPP
