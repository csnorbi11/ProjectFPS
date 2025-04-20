#ifndef SCENE_HPP
#define SCENE_HPP
#include <vector>

class GameObject;
class Camera;
class Light;
class Map;

struct Scene {
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    std::unique_ptr<Camera> camera;
    std::unique_ptr<Map> loadedMap;
    std::vector<std::unique_ptr<Light>> lights;
};

#endif //SCENE_HPP
