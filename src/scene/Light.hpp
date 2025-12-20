#ifndef LIGHT_HPP
#define LIGHT_HPP
#include <glm/vec3.hpp>

#include "../graphics/ShaderProgram.hpp"
#include "graphics/Material.hpp"
#include "game/AssetManager.hpp"


struct LightParams {
	glm::vec3 color{ 1.f };
	float intensity = 1;
};

class Light {
public:
	explicit Light(const LightParams& params);
	virtual ~Light();

	virtual void apply(ShaderProgram* program) = 0;

	virtual void setColor(glm::vec3 color);
	virtual void setIntensity(float intensity);
	virtual void setColorAndIntensity(glm::vec3 color, float intensity);

	glm::vec3 getColor();
	float getIntensity();

protected:
	glm::vec3 color;
	float intensity;
};


#endif //LIGHT_HPP
