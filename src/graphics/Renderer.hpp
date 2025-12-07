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

    void drawObjects(const std::vector<GameObject*>& objects);

    template<typename T>
    void drawObject(T* object) {






    }
	template<typename T>
    void drawObjects(std::vector<std::unique_ptr<T>>& objects) {
        if (!isShaderProgramActive("basic")) {
            activeShaderProgram = "basic";
            assetManager.getShaderPrograms()[activeShaderProgram]->use();

        }



        for (const auto& object : objects) {


            applyDirectionalLight();
            applyPointLights();
			drawObject<T>(object.get());
        }

        glBindVertexArray(0);
        glActiveTexture(GL_TEXTURE0);
    }
    template<>
    void drawObjects<PointLight>(std::vector<std::unique_ptr<PointLight>>& objects);


    void drawMap();


    std::string activeShaderProgram={};

    Scene* activeScene=nullptr;
    uint32_t activeVAO = 0;

    bool debugMode=false;

    GLFWHandler& glfwHandler;
	AssetManager& assetManager;

};

#endif //RENDERER_HPP