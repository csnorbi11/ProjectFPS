#include <utility>
#include <stdexcept>
#include <vector>

#include "Map.hpp"


Map::Map(std::unique_ptr<DirectionalLight> dirLight, AssetManager& assetManager)
	:
	directionalLight(std::move(dirLight))
{

}

void Map::addObject(std::unique_ptr<StaticObject> object)
{
	if (object) {
		objects.push_back(std::move(object));
	}
	else {
		throw std::runtime_error("Cannot add a null object to the map.");
	}
}

void Map::addPointLight(std::unique_ptr<PointLight> pointLight)
{
	if (pointLight) {
		pointLights.push_back(std::move(pointLight));
	}
	else {
		throw std::runtime_error("Cannot add a null object to the map.");
	}
}

void Map::setDirectionalLight(std::unique_ptr<DirectionalLight> light)
{
	if (light) {
		directionalLight = std::move(light);
	}
	else {
		throw std::runtime_error("Cannot add a null object to the map.");
	}
}

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
