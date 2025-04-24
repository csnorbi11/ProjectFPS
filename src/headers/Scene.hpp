#ifndef SCENE_HPP
#define SCENE_HPP
#include <memory>
#include <vector>

class PointLight;
class DirectionalLight;
class GameObject;
class Camera;
class Map;

struct Scene {
    std::vector<std::unique_ptr<GameObject>> gameObjects{};
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Map> loadedMap;
    std::unique_ptr<DirectionalLight> directionalLight;
    std::vector<std::unique_ptr<PointLight>> pointLights{};

    void update(double deltaTime);
};

#endif //SCENE_HPP
