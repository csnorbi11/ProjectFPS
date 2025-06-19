#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <memory>

#include "BSPTree.hpp"
#include "StaticObject.hpp"

class Map {
public:
    Map();
    ~Map();

private:
    std::vector<StaticObject> objects;
	std::unique_ptr<BSPTree> bspTree;
};

#endif //MAP_HPP
