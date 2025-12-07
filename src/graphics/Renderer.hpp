#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <unordered_map>
#include <glad/glad.h>
#include <string>

#include "../scene/Light.hpp"
#include "../scene/Scene.hpp"
#include "../platform/GLFWHandler.hpp"
#include "../game/AssetManager.hpp"


class Renderer {
public:
    Renderer(GLFWHandler& glfwHandler, AssetManager& assetManager);
    ~Renderer();


    void drawScene();
    void update();

    void setActiveScene(Scene* scene);
private:
    bool isShaderProgramActive(const std::string& programName) const;

    void viewProjection();
    void applyDirectionalLight();
    void applyPointLights();

    template<typename T>
    void drawObject(T* object) {



        glm::mat4 transformMatrix(1.f);
        transformMatrix = glm::translate(glm::mat4(1.0f), object->position);
        transformMatrix *= static_cast<glm::mat4>(object->getQuaternion());
        assetManager.getShaderPrograms()[activeShaderProgram]->setVec3("viewPos", activeScene->camera->position);
        assetManager.getShaderPrograms()[activeShaderProgram]->setMat4("model", transformMatrix);
        viewProjection();
        assetManager.getShaderPrograms()[activeShaderProgram]->setVec3("material.ambient", { 1.0f, 0.5f, 0.31f });
        assetManager.getShaderPrograms()[activeShaderProgram]->setVec3("material.diffuse", { 1.0f, 0.5f, 0.31f });
        assetManager.getShaderPrograms()[activeShaderProgram]->setVec3("material.specular", { 0.1f, 0.1f, 0.1f });
        assetManager.getShaderPrograms()[activeShaderProgram]->setFloat("material.shininess", 32.0f);
        Model* model = object->getModel();
        if (!model)return;
        for (const auto& mesh : model->getMeshes()) {


            assetManager.getShaderPrograms()[activeShaderProgram]->setBool("hasTexture", !(mesh->getTextures().empty()));
            for (int i = 0;i < mesh->getTextures().size();i++) {
                glActiveTexture(GL_TEXTURE0 + i);
                std::string name = mesh->getTextures()[i].type;
                if (name == "texture_diffuse") {
                    assetManager.getShaderPrograms()[activeShaderProgram]->setInt("material.diffuse", i);
                }
                else if (name == "texture_specular") {
                    assetManager.getShaderPrograms()[activeShaderProgram]->setInt("material.specular", i);
                }


                glBindTexture(GL_TEXTURE_2D, mesh->getTextures()[i].id);
            }
            mesh->bindVAO();
            glDrawElements(GL_TRIANGLES, static_cast<int>(mesh->getIndices().size()), GL_UNSIGNED_INT, 0);
            mesh->unbindVAO();
            glActiveTexture(GL_TEXTURE0);
        }
    }
	template<typename T>
    void drawObjects(std::vector<std::unique_ptr<T>>& objects) {
        for (const auto& object : objects) {

            if (!isShaderProgramActive("basic")) {
                activeShaderProgram = "basic";
                assetManager.getShaderPrograms()[activeShaderProgram]->use();
                applyDirectionalLight();
                applyPointLights();
			}

			drawObject<T>(object.get());
        }
    }
    template<>
    void drawObjects<PointLight>(std::vector<std::unique_ptr<PointLight>>& objects);


    void drawMap();


    std::string activeShaderProgram={};

    Scene* activeScene=nullptr;

    bool debugMode=false;

    GLFWHandler& glfwHandler;
	AssetManager& assetManager;

};

#endif //RENDERER_HPP