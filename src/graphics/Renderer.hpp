#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <unordered_map>
#include <glad/glad.h>
#include <string>

#include "../scene/Light.hpp"
#include "../scene/Scene.hpp"
#include "../platform/GLFWHandler.hpp"
#include "Shader.hpp"
#include "ShaderProgram.hpp"
#include "Model.hpp"


class Renderer {
public:
    Renderer(GLFWHandler& glfwHandler);
    ~Renderer();


    void createShaderProgram(const std::string &name,
                             const std::string &vertexShader, const std::string &fragmentShader);

    void drawScene();

    

    void update();

    void setActiveScene(Scene* scene);

private:

    bool isModelLoaded(const std::string& path) const;
    bool isShaderProgramActive(const std::string& programName) const;

    void viewProjection();
    void applyDirectionalLight();
    void applyPointLights();

    template<typename T>
    void drawObject(T* object) {



        glm::mat4 transformMatrix(1.f);
        transformMatrix = glm::translate(glm::mat4(1.0f), object->position);
        transformMatrix *= static_cast<glm::mat4>(object->getQuaternion());
        shaderPrograms[activeShaderProgram]->setVec3("viewPos", activeScene->camera->position);
        shaderPrograms[activeShaderProgram]->setMat4("model", transformMatrix);
        viewProjection();
        shaderPrograms[activeShaderProgram]->setVec3("material.ambient", { 1.0f, 0.5f, 0.31f });
        shaderPrograms[activeShaderProgram]->setVec3("material.diffuse", { 1.0f, 0.5f, 0.31f });
        shaderPrograms[activeShaderProgram]->setVec3("material.specular", { 0.1f, 0.1f, 0.1f });
        shaderPrograms[activeShaderProgram]->setFloat("material.shininess", 32.0f);
        Model* model = models[object->getModelPath()].get();
        for (const auto& mesh : model->getMeshes()) {

            shaderPrograms[activeShaderProgram]->setBool("hasTexture", !(mesh->getTextures().empty()));
            for (int i = 0;i < mesh->getTextures().size();i++) {
                glActiveTexture(GL_TEXTURE0 + i);
                std::string name = mesh->getTextures()[i].type;
                if (name == "texture_diffuse") {
                    shaderPrograms[activeShaderProgram]->setInt("material.diffuse", i);
                }
                else if (name == "texture_specular") {
                    shaderPrograms[activeShaderProgram]->setInt("material.specular", i);
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
            if (!isModelLoaded(object->getModelPath())) {
				loadModel(object->getModelPath(), "basic");
            }
            if (!isShaderProgramActive("basic")) {
                activeShaderProgram = "basic";
                shaderPrograms[activeShaderProgram]->use();
                applyDirectionalLight();
                applyPointLights();
			}

			drawObject<T>(object.get());
        }
    }
    template<>
    void drawObjects<PointLight>(std::vector<std::unique_ptr<PointLight>>& objects);


    void drawMap();

    void loadShader(const std::string &path, GLenum shaderType);
    void loadModel(const std::string &path, const std::string &shaderProgName);

    std::unordered_map<std::string, std::unique_ptr<Shader> > shaders = {};
    std::unordered_map<std::string, std::unique_ptr<ShaderProgram> > shaderPrograms = {};
    std::unordered_map<std::string, std::unique_ptr<Model> > models={};

    std::string activeShaderProgram={};

    Scene* activeScene=nullptr;

    bool debugMode=false;

    GLFWHandler& glfwHandler;

};

#endif //RENDERER_HPP