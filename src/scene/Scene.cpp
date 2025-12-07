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


Scene::Scene(std::string mapPath, AssetManager& assetManager)
{
    

    std::stringstream buffer;
    std::ifstream file{ mapPath };

    if (file) {
        buffer << file.rdbuf();
        file.close();
    }

    std::string line;
    std::unique_ptr<DirectionalLight> dirLight;
    std::unordered_set<std::string> modelsToLoad;
    std::string objType, modelPath;
    glm::vec3 position;
    while (std::getline(buffer, line)) {

        std::stringstream sline{ line };

        sline >> objType >> modelPath;
        

        if (objType == "OBJECT"|| objType == "LIGHT") {
            modelsToLoad.insert(modelPath);
        }else if (objType == "DIRLIGHT") {
            
            glm::vec3 direction{ 0.f,-1.f,0.f };
            float intensity=0.5f;
            glm::vec3 ambient{ 1.f }, diffuse{ 1.f }, specular{ 1.f };
            dirLight = std::make_unique<DirectionalLight>(
                DirectionalLightParams{ direction ,intensity},
                LightParams{ambient,diffuse,specular}
            );
        }
    }

    map = std::make_unique<Map>(std::move(dirLight));

    buffer.clear();
    buffer.seekg(0);
    for (const auto& modelPath : modelsToLoad) {
        requestToLoadModels(assetManager, modelPath);
    }

    while (std::getline(buffer, line)) {

        std::stringstream sline{ line };
        
        sline >> objType;
        if (objType == "OBJECT") {
            sline >> modelPath >> position.x >> position.y >> position.z;
            map->addObject(std::make_unique<StaticObject>( GameObjectParams{assetManager.getModel(modelPath),position }));
        }
        else if(objType=="LIGHT") {
            float constant, linear, quadratic;
            glm::vec3 ambient, diffuse, specular;
            sline>> objType >> modelPath >> position.x >> position.y >> position.z;
            map->addPointLight(std::make_unique<PointLight>(
                PointLightParams{},
                LightParams{},
            GameObjectParams{ assetManager.getModel(modelPath), position }
            ));
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
