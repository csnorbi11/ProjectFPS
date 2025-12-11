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
            glm::vec3 ambient{ 1.f }, diffuse{ 1.f }, specular{ 1.f };
            sline >> direction.x >> direction.y >> direction.z >> intensity >> ambient.x >> ambient.y >> ambient.z >>
                diffuse.x >> diffuse.y >> diffuse.z >> specular.x >> specular.y >> specular.z;

            if (glm::length(direction)>1) {
                direction = glm::normalize(direction);
            }
            if (glm::length(ambient) > 1) {
                ambient = glm::normalize(ambient);
            }
            if (glm::length(diffuse) > 1) {
                diffuse = glm::normalize(diffuse);
            }
            if (glm::length(specular) > 1) {
                specular = glm::normalize(specular);
            }
            dirLight = std::make_unique<DirectionalLight>(
                DirectionalLightParams{ direction ,intensity},
                LightParams{ambient,diffuse,specular}
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
            
            map->addObject(std::make_unique<StaticObject>(GameObjectParams{ assetManager.getModel(modelName),{},position }));
        }
        else if(objType=="LIGHT") {
            float constant, linear, quadratic;
            glm::vec3 ambient, diffuse, specular;
            sline>> objType >> modelPath >> position.x >> position.y >> position.z;
            size_t lastSlash = modelPath.find_last_of('/')+1;
            std::string modelName = lastSlash != std::string::npos&&lastSlash!=0 ? modelPath.substr(lastSlash) : modelPath;
            map->addPointLight(std::make_unique<PointLight>(
                PointLightParams{},
                LightParams{},
                GameObjectParams{ assetManager.getModel(modelName),{}, position }
            ));
        }
        
    }

    std::vector<Material*> mats;
    mats.push_back(assetManager.getMaterials()["pointLight"].get());

    map->addPointLight((std::make_unique<PointLight>(PointLightParams{ static_cast<uint32_t>(map->getPointLights().size()),
        1.f,0.22f,.20f }, LightParams{}, GameObjectParams{ assetManager.getModel("assets/models/cube.obj"), mats })));
    map->getPointLights()[0]->position = glm::vec3(35.0f, 4.0f, 5.0f);
    map->getPointLights()[0]->setOverallColor({ 0.3f,0.9f,1.f });

    map->addPointLight((std::make_unique<PointLight>(PointLightParams{ static_cast<uint32_t>(map->getPointLights().size()),
        1.f,0.22f,.20f }, LightParams{}, GameObjectParams{ assetManager.getModel("assets/models/cube.obj"), mats })));
    map->getPointLights()[1]->position = glm::vec3(26.0f, 1.0f, -2.0f);
    map->getPointLights()[1]->setOverallColor({ 1.0f,0.3f,0.f });
    map->addPointLight((std::make_unique<PointLight>(PointLightParams{ static_cast<uint32_t>(map->getPointLights().size()),
        1.f,0.22f,.20f }, LightParams{}, GameObjectParams{ assetManager.getModel("assets/models/cube.obj"), mats })));
    map->getPointLights()[2]->position = glm::vec3(22.0f, 3.0f, -2.0f);
    map->getPointLights()[2]->setOverallColor({ 1.0f,0.9f,0.f });
}

void Scene::update(double deltaTime) {

    camera->update(static_cast<float>(deltaTime));
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
