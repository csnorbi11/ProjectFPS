#ifndef SCENE_HPP
#define SCENE_HPP
#include <memory>
#include <vector>

#include "Map.hpp"
#include "Player.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Enemy.hpp"
#include "DynamicObject.hpp"

struct Scene {
    std::unique_ptr<Map> map;
	std::vector<std::unique_ptr<Light>> dynamicLights;
    std::vector<std::unique_ptr<Enemy>> enemies;
    std::unique_ptr<Player> player;
    std::unique_ptr<Camera> camera;
	std::vector<std::unique_ptr<DynamicObject>> dynamicObjects;

    void update(double deltaTime);
};

#endif //SCENE_HPP
