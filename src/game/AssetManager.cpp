#include "AssetManager.hpp"
#include <iostream>

void AssetManager::loadModel(const std::string& path, const std::string& shaderProgName)
{
	if (models.count(path) == 0) {
		models.emplace(path, std::make_unique<Model>(path, shaderProgName));
	}
	else {
		std::cerr << "Model already loaded: " << path << std::endl;
	}
}

void AssetManager::loadShader(const std::string& path, GLenum shaderType)
{
	if (shaders.count(path) == 0) {
		shaders.emplace(path, std::make_unique<Shader>(path.c_str(), shaderType));
	}
	else {
		std::cerr << "Shader already loaded: " << path << std::endl;
	}
}

void AssetManager::createShaderProgram(const std::string& name, const std::string& vertexShader, const std::string& fragmentShader)
{
	if (shaders.count(vertexShader) == 0) {
		loadShader(vertexShader, GL_VERTEX_SHADER);
	}
	if (shaders.count(fragmentShader) == 0) {
		loadShader(fragmentShader, GL_FRAGMENT_SHADER);
	}
	shaderPrograms.emplace(name, std::make_unique<ShaderProgram>(*shaders[vertexShader],
		*shaders[fragmentShader]));
}

std::unordered_map<std::string, std::unique_ptr<Model>>& AssetManager::getModels()
{
	return models;
}

std::unordered_map<std::string, std::unique_ptr<ShaderProgram>>& AssetManager::getShaderPrograms()
{
	return shaderPrograms;
}

bool AssetManager::isModelLoaded(const std::string& path) const
{
	return !(models.count(path) == 0);
}


