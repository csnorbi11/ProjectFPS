#ifndef BSPNODE_HPP
#define BSPNODE_HPP
#include <glm/vec3.hpp>

struct BSPNode {
  glm::vec3 planeNormal;
  BSPNode *front, *back;
};

#endif //BSPNODE_HPP
