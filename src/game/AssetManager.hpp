#ifndef ASSETMANAGER_HPP
#define ASSETMANAGER_HPP

#include <memory>
#include <unordered_map>
#include <glad/glad.h>

#include "graphics/Model.hpp"
#include "graphics/Shader.hpp"
#include "graphics/ShaderProgram.hpp"
#include "graphics/Material.hpp"


class AssetManager {
public:
	AssetManager() = default;
	~AssetManager() = default;

	void loadModel(const std::string& path, const std::string& shaderProgName);
	bool isModelLoaded(const std::string& path) const;
	
	void loadTexture(const std::string& path, const std::string& name, const std::string& type, bool flip = false);

	void createMaterial(const std::string& name, const std::string& programName,
		const MaterialParam& matParam, const MaterialTextureParam& matTexture);
	
	void createShaderProgram(const std::string& name,
		const std::string& vertexShader, const std::string& fragmentShader);

	Model* getModel(std::string model);

	std::unordered_map<std::string, std::unique_ptr<Model> >& getModels();
	std::unordered_map<std::string, std::unique_ptr<ShaderProgram> >& getShaderPrograms();
	std::unordered_map<std::string, std::unique_ptr<Texture> >& getTextures();
	std::unordered_map<std::string, std::unique_ptr<Material> >& getMaterials();

private:
	void loadShader(const std::string& path, GLenum shaderType);

	std::unordered_map<std::string, std::unique_ptr<Shader> > shaders = {};
	std::unordered_map<std::string, std::unique_ptr<ShaderProgram> > shaderPrograms = {};
	std::unordered_map<std::string, std::unique_ptr<Material> > materials= {};
	std::unordered_map<std::string, std::unique_ptr<Texture> > textures= {};
	std::unordered_map<std::string, std::unique_ptr<Model> > models = {};
};



#endif