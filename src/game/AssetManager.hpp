#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <glad/glad.h>

#include "../graphics/Model.hpp"
#include "../graphics/Shader.hpp"
#include "../graphics/ShaderProgram.hpp"


class AssetManager {
public:
	AssetManager() = default;
	~AssetManager() = default;


	void loadModel(const std::string& path, const std::string& shaderProgName);
	void createShaderProgram(const std::string& name,
		const std::string& vertexShader, const std::string& fragmentShader);

	Model const* getModel(const std::string& path, const std::string& shaderProgName);

	std::unordered_map<std::string, std::unique_ptr<Model> >& getModels();
	std::unordered_map<std::string, std::unique_ptr<ShaderProgram> >& getShaderPrograms();

private:
	void loadShader(const std::string& path, GLenum shaderType);

	
	bool isModelLoaded(const std::string& path) const;

	std::unordered_map<std::string, std::unique_ptr<Shader> > shaders = {};
	std::unordered_map<std::string, std::unique_ptr<ShaderProgram> > shaderPrograms = {};
	std::unordered_map<std::string, std::unique_ptr<Model> > models = {};
};



#endif