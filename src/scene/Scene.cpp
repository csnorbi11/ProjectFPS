#include "Scene.hpp"

#include <iostream>
#include <ostream>
#include <memory>
#include <fstream>
#include <sstream>

#include "Camera.hpp"
#include "GameObject.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"
#include "Map.hpp"
#include <unordered_set>

#include <nlohmann/json.hpp>
#include <glm/glm.hpp>

using json = nlohmann::json;

Scene::Scene(std::string mapPath, AssetManager& assetManager)
{



	map = std::make_unique<Map>();

	std::ifstream file{ mapPath };

	if (!file) {
		return;
	}

	json data = json::parse(file);
	file.close();

	std::unordered_set<std::string> modelsToLoad;


	for (const auto& obj : data["objects"]) {
		std::string type = obj["type"];
		std::string modelPath = obj["model"];
		glm::vec3 pos{ obj["position"][0],obj["position"][1] ,obj["position"][2] };
		glm::vec3 rot{ obj["rotation"][0],obj["rotation"][1] ,obj["rotation"][2] };
		size_t lastSlash = modelPath.find_last_of('/') + 1;
		std::string modelName = lastSlash != std::string::npos ? modelPath.substr(lastSlash) : modelPath;


		if (assetManager.getModels().count(modelName) == 0) {
			assetManager.loadModel(modelPath);
		}
		if (type == "static") {
			map->addObject(std::make_unique<StaticObject>(GameObjectParams{ assetManager.getModel(modelName),pos, rot }));
		}
	}
	for (const auto& obj : data["lights"]) {
		std::string type{ obj["type"] };

		glm::vec3 color{ obj["color"][0],obj["color"][1] ,obj["color"][2] };
		float intensity{ obj["intensity"] };



		if (type == "POINT") {
			if (assetManager.getModels().count("cube.obj") == 0) {
				assetManager.loadModel("assets/models/cube.obj");
			}
			glm::vec3 pos{ obj["position"][0],obj["position"][1] ,obj["position"][2] };
			glm::vec3 rot{ obj["rotation"][0],obj["rotation"][1] ,obj["rotation"][2] };
			map->addPointLight(std::make_unique<PointLight>(assetManager, PointLightParams{ map->getPointLights().size() }, LightParams{ color,intensity },
				GameObjectParams{ assetManager.getModel("cube.obj"),pos }));
		}
		else if (type == "SUN") {

			glm::vec3 dir{ obj["direction"][0],obj["direction"][1] ,obj["direction"][2] };

			dir = glm::normalize(dir);

			map->setDirectionalLight(std::make_unique<DirectionalLight>(
				DirectionalLightParams{ dir }, LightParams{ color,intensity }
			));
		}

	}

}

void Scene::update(double deltaTime) {

	camera->update(static_cast<float>(deltaTime));
	for (auto& obj : getAllObjects()) {
		obj->update(static_cast<float>(deltaTime));
	}
}

void Scene::requestToLoadModels(AssetManager& assetManager, std::string modelPath)
{
	assetManager.loadModel(modelPath);
}

std::vector<GameObject*> Scene::getAllObjects() const
{

	size_t size = map->getObjects().size() + map->getPointLights().size() +
		dynamicLights.size() + enemies.size() + dynamicObjects.size();

	std::vector<GameObject*> objects;
	objects.reserve(size);

	for (auto& obj : map->getObjects()) {
		objects.push_back(obj.get());
	}
	for (auto& obj : map->getPointLights()) {
		objects.push_back(obj.get());
	}

	for (auto& obj : dynamicLights) {
		objects.push_back(obj.get());
	}
	for (auto& obj : enemies) {
		objects.push_back(obj.get());
	}
	for (auto& obj : dynamicObjects) {
		objects.push_back(obj.get());
	}

	return objects;
}
