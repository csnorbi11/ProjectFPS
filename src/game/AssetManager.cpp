#include "AssetManager.hpp"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "graphics/Model.hpp"

void AssetManager::loadModel(const std::string& path)
{
    std::string name = path.substr(path.find_last_of('/')+1);
	if (models.count(name) == 0) {
		std::cout <<"Loading model: " << name << std::endl;
		models.emplace(name, std::make_unique<Model>(path, *this));
        if (models[name]->getMeshes().empty()) {
            std::cout << "Cant model: " << name << std::endl;
        }
        else {
            std::cout << "Loaded model: " << name << std::endl;
        }
	}
	else {
		std::cerr << "Model already loaded: " << path << std::endl;
	}
}

void AssetManager::loadShader(const std::string& path, GLenum shaderType)
{
	if (shaders.count(path) == 0) {
		std::cout << "Shader loaded: " << path << std::endl;
		shaders.emplace(path, std::make_unique<Shader>(path.c_str(), shaderType));
	}
	else {
		std::cerr << "Shader already loaded: " << path << std::endl;
	}
}

void AssetManager::createMaterial(const std::string& name, const std::string& programName, const MaterialParam& matParam, const MaterialTextureParam& matTexture)
{
    if (shaders.count(name) == 0) {
        std::cout << "Material created: " << name<< std::endl;
        materials.emplace(name, std::make_unique<Material>(name, shaderPrograms[programName].get(), matParam, matTexture));
    }
    else {
        std::cerr << "Material done: " << name << std::endl;
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

Model* AssetManager::getModel(std::string model)
{
    return models.count(model) != 0 ? models[model].get() : nullptr;
}

std::unordered_map<std::string, std::unique_ptr<Model>>& AssetManager::getModels()
{
	return models;
}

std::unordered_map<std::string, std::unique_ptr<ShaderProgram>>& AssetManager::getShaderPrograms()
{
	return shaderPrograms;
}

std::unordered_map<std::string, std::unique_ptr<Texture>>& AssetManager::getTextures()
{
    return textures;
}

std::unordered_map<std::string, std::unique_ptr<Material>>& AssetManager::getMaterials()
{
    return materials;
}

void AssetManager::loadTexture(const std::string& name, const std::string& path, const std::string& type, bool flip)
{
    //std::string filename = std::string(path);

    unsigned int textureID;
    glGenTextures(1, &textureID);
    stbi_set_flip_vertically_on_load(flip);
    int width, height, nrComponents;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &nrComponents, 0);
    if (data)
    {
        GLenum format;
        if (nrComponents == 1)
            format = GL_RED;
        else if (nrComponents == 3)
            format = GL_RGB;
        else if (nrComponents == 4)
            format = GL_RGBA;

        glBindTexture(GL_TEXTURE_2D, textureID);
        glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(data);
    }
    else
    {
        std::cout << "Texture failed to load at path: " << path << std::endl;
        stbi_image_free(data);
    }

    textures.emplace(name, std::make_unique<Texture>(name, path, textureID, type));
}


