#include <utility>

#include "Map.hpp"

std::vector<std::unique_ptr<StaticObject>>& Map::getObjects()
{
	return objects;
}

std::vector<std::unique_ptr<PointLight>>& Map::getPointLights()
{
    return pointLights;
}

DirectionalLight& Map::getDirectionalLight()
{
	return *directionalLight;
}
