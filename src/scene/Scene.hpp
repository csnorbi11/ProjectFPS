#ifndef SCENE_HPP
#define SCENE_HPP
#include <memory>
#include <vector>

#include "Map.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include "game/AssetManager.hpp"
#include "Enemy.hpp"
#include "DynamicObject.hpp"
#include <string>

struct Scene {

    Scene() = default;
    Scene(std::string mapPath, AssetManager& assetManager);

    ~Scene() = default;

    void update(double deltaTime);
    void requestToLoadModels(AssetManager& assetManager, std::string modelPath);

    std::vector<GameObject*> getAllObjects() const;


    std::unique_ptr<Map> map;
	std::vector<std::unique_ptr<PointLight>> dynamicLights;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::unique_ptr<Player> player;
    std::unique_ptr<Camera> camera;
	std::vector<std::unique_ptr<DynamicObject>> dynamicObjects;


};

#endif //SCENE_HPP
