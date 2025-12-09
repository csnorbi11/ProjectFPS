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

	if (!hasTexture)
		return;

	program->setBool("hasTexture", hasTexture);
	if (diffuseMap) {
		// Ahol a textúrát bindolod:
		if (!glIsTexture(diffuseMap->id)) {
			std::cout << "HIBA: Érvénytelen textúrát próbálunk bindolni! ID: " << diffuseMap->id << std::endl;
		}
		glBindTexture(GL_TEXTURE_2D, diffuseMap->id);
		program->setInt("material.diffuse", diffuseMapID);
	}
	if (specularMap) {
		program->setInt("material.specular", specularMapID);
	}
	if (normalMap) {
		program->setInt("material.specular", normalMapID);
	}

}

const std::string& Material::getName()
{
	return name;
}
