#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <memory>

#include "StaticObject.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"
#include "BSPTree.hpp"

class Map {
public:
    Map();
    ~Map();

private:
    std::vector<std::unique_ptr<StaticObject>> objects;
	std::vector<std::unique_ptr<PointLight>> pointLights;
	std::unique_ptr<DirectionalLight> directionalLight;

	std::unique_ptr<BSPTree> bspTree;
    
};

#endif //MAP_HPP
