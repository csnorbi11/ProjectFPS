#include <utility>

#include "Map.hpp"
#include <stdexcept>

Map::Map()
{
	directionalLight = std::make_unique<DirectionalLight>();

	//pointLights[0]->position = glm::vec3(35.0f, 4.0f, 5.0f);
	//pointLights[0]->setOverallColor({ 0.3f,0.9f,1.f });

	//pointLights[1]->position = glm::vec3(26.0f, 1.0f, -2.0f);
	//pointLights[1]->setOverallColor({ 1.0f,0.3f,0.f });
	//pointLights.emplace_back(std::make_unique<PointLight>(PointLightParams{ static_cast<uint32_t>(pointLights.size()),
	//	1.f,0.22f,.20f }));
	//pointLights[2]->position = glm::vec3(22.0f, 3.0f, -2.0f);
	//pointLights[2]->setOverallColor({ 1.0f,0.9f,0.f });
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
