#include "Material.hpp"
#include <iostream>

Material::Material(const std::string& name, ShaderProgram* program, const MaterialParam& matParam, const MaterialTextureParam& matTexture)
	:
	name(name),
	program(program),
	ambient(matParam.ambient),
	diffuse(matParam.diffuse),
	specular(matParam.specular),
	shininess(matParam.shininess),
	diffuseMap(matTexture.diffuseMap),
	specularMap(matTexture.specularMap),
	normalMap(matTexture.normalMap)
{
	if (diffuseMap || specularMap || normalMap) {
		hasTexture = true;
	}
}

Material::~Material()
{
	diffuseMap = nullptr;
	specularMap = nullptr;
	normalMap = nullptr;
	program = nullptr;
}

void Material::apply() const
{
	program->setVec3("material.ambient", ambient);
	program->setVec3("material.diffuse", diffuse);
	program->setVec3("material.specular", specular);
	program->setFloat("material.shininess", shininess);

	program->setBool("hasTexture", hasTexture);

	if (!hasTexture)
		return;

	if (diffuseMap) {
		glActiveTexture(GL_TEXTURE0 + diffuseMapID);
		program->setInt("texMat.diffuse", diffuseMapID);
		glBindTexture(GL_TEXTURE_2D, diffuseMap->id);
	}
	if (specularMap) {
		glActiveTexture(GL_TEXTURE0 + specularMapID);
		program->setInt("texMat.specular", specularMapID);
		glBindTexture(GL_TEXTURE_2D, specularMap->id);
	}
	if (normalMap) {
		glActiveTexture(GL_TEXTURE0 + normalMapID);
		program->setInt("texMat.specular", normalMapID);
		glBindTexture(GL_TEXTURE_2D, normalMap->id);
	}

}

const std::string& Material::getName()
{
	return name;
}
