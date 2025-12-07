#include "Scene.hpp"

#include <iostream>
#include <ostream>
#include <GLFW/glfw3.h>
#include <fstream>
#include <sstream>

#include "Camera.hpp"
#include "GameObject.hpp"
#include "PointLight.hpp"
#include <unordered_set>


Scene::Scene(std::string mapPath, AssetManager& assetManager)
{
    map = std::make_unique<Map>();

    std::stringstream buffer;
    std::ifstream file{ mapPath };

    if (file) {
        buffer << file.rdbuf();
        file.close();
    }

    std::string line;

    std::unordered_set<std::string> modelsToLoad;
    std::string objType, modelPath;
    glm::vec3 position;
    while (std::getline(buffer, line)) {

        std::stringstream sline{ line };

        sline >> objType >> modelPath;


        if (objType == "OBJECT") {
            modelsToLoad.insert(modelPath);
        }
    }
    buffer.clear();
    buffer.seekg(0);
    for (const auto& modelPath : modelsToLoad) {
        requestToLoadModels(assetManager, modelPath);
    }

    while (std::getline(buffer, line)) {

        std::stringstream sline{ line };
        sline >> objType >> modelPath >> position.x >> position.y >> position.z;

        if (objType == "OBJECT") {
            map->addObject(std::make_unique<StaticObject>( GameObjectParams{assetManager.getModel(modelPath),position }));
        }
        else if(objType=="LIGHT") {
           // map->addPointLight(std::make_unique<PointLight>());
        }
    }
}

void Scene::update(double deltaTime) {

    camera->update(static_cast<float>(deltaTime));
}

void Scene::requestToLoadModels(AssetManager& assetManager, std::string modelPath)
{
    assetManager.loadModel(modelPath, "basic");
}

std::vector<GameObject*> Scene::getAllObjects() const
{

    size_t size = map->getObjects().size() + map->getPointLights().size() +
        dynamicLights.size() + enemies.size() + dynamicLights.size();

    std::vector<GameObject*> objects{size};

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
