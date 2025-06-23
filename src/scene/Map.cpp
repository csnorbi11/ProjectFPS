#include <utility>
#include <stdexcept>

#include "Map.hpp"
#include "../graphics/Renderer.hpp"

Map::Map(Renderer* renderer)
{
	directionalLight = std::make_unique<DirectionalLight>();
	directionalLight->setIntensity(0.5f);
	directionalLight->setAmbient({ 1.f,1.f,1.f });
	directionalLight->setDiffuse({ 1.f,1.f,1.f });
	directionalLight->setSpecular({ 1.f,1.f,1.f });

	addObject(std::make_unique<StaticObject>(GameObjectParams{ "assets/models/testMap.obj" }));

	pointLights.emplace_back(std::make_unique<PointLight>(PointLightParams{ static_cast<uint32_t>(pointLights.size()),
		1.f,0.22f,.20f }));
	pointLights[0]->position = glm::vec3(35.0f, 4.0f, 5.0f);
	pointLights[0]->setOverallColor({ 0.3f,0.9f,1.f });

	pointLights.emplace_back(std::make_unique<PointLight>(PointLightParams{ static_cast<uint32_t>(pointLights.size()),
		1.f,0.22f,.20f }));
	pointLights[1]->position = glm::vec3(26.0f, 1.0f, -2.0f);
	pointLights[1]->setOverallColor({ 1.0f,0.3f,0.f });
	pointLights.emplace_back(std::make_unique<PointLight>(PointLightParams{ static_cast<uint32_t>(pointLights.size()),
		1.f,0.22f,.20f }));
	pointLights[2]->position = glm::vec3(22.0f, 3.0f, -2.0f);
	pointLights[2]->setOverallColor({ 1.0f,0.9f,0.f });

	addObject(std::make_unique<StaticObject>(GameObjectParams{ "assets/models/backpack/backpack.obj",glm::vec3(30.f,1.f,6.f) }));
	addObject(std::make_unique<StaticObject>(GameObjectParams{ "assets/models/backpack/backpack.obj",glm::vec3(30.f,1.f,-6.f) }));

	for (auto& object : objects) {
		std::string modelPath = object->getModelPath();
		if(!renderer->isModelLoaded(modelPath))
			renderer->loadModel(modelPath, "basic");
	}
	bspTree = std::make_unique<BSPTree>(objects, renderer);
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

void Map::generateBSPTree(Renderer* renderer)
{
	bspTree = std::make_unique<BSPTree>(objects, renderer);
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
