#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <memory>

#include "StaticObject.hpp"
#include "PointLight.hpp"
#include "DirectionalLight.hpp"
#include "game/AssetManager.hpp"

class Map {
public:
	Map(AssetManager& assetManager);
	Map(std::unique_ptr<DirectionalLight> dirLight);
	~Map() = default;

	void addObject(std::unique_ptr<StaticObject> object);
	void addPointLight(std::unique_ptr<PointLight> pointLight);
	void setDirectionalLight(std::unique_ptr<DirectionalLight> light);

	std::vector<std::unique_ptr<StaticObject>>& getObjects();
	std::vector<std::unique_ptr<PointLight>>& getPointLights();
	DirectionalLight& getDirectionalLight();

private:
    std::vector<std::unique_ptr<StaticObject>> objects;
	std::vector<std::unique_ptr<PointLight>> pointLights;
	std::unique_ptr<DirectionalLight> directionalLight;
    
};

#endif //MAP_HPP
