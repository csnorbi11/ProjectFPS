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
            
            glm::vec3 direction{ -0.5f,-0.5f,0.f };
            float intensity=0.5f;
            glm::vec3 color{};
            sline >> direction.x >> direction.y >> direction.z >> intensity >> color.x >> color.y >> color.z;

            dirLight = std::make_unique<DirectionalLight>(
                DirectionalLightParams{ direction},
                LightParams{color,intensity}
            );
        }
    }

    map = std::make_unique<Map>(std::move(dirLight),assetManager);

    buffer.clear();
    buffer.seekg(0);
    for (const auto& path : modelsToLoad) {
        requestToLoadModels(assetManager, path);
    }

    while (std::getline(buffer, line)) {

        std::stringstream sline{ line };
        
        sline >> objType;
        if (objType == "OBJECT") {
            sline >> modelPath >> position.x >> position.y >> position.z;
            size_t lastSlash = modelPath.find_last_of('/')+1;
            std::string modelName = lastSlash != std::string::npos ? modelPath.substr(lastSlash) : modelPath;
            
            map->addObject(std::make_unique<StaticObject>(GameObjectParams{ assetManager.getModel(modelName),position }));
        }
        else if(objType=="LIGHT") {
            float constant, linear, quadratic;
            glm::vec3 color{};
            sline >> modelPath >> position.x >> position.y >> position.z >> color.x >> color.y >> color.z;

            size_t lastSlash = modelPath.find_last_of('/')+1;
            std::string modelName = lastSlash != std::string::npos&&lastSlash!=0 ? modelPath.substr(lastSlash) : modelPath;
            PointLight* light = new PointLight{assetManager, PointLightParams{map->getPointLights().size(),1.f,0.22f,.20f },
                LightParams{color, 1.f},
                GameObjectParams{ assetManager.getModel(modelName), position}};
            map->addPointLight(std::unique_ptr<PointLight>(light));
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
