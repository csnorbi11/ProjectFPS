#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <unordered_map>
#include <glad/glad.h>
#include <string>

#include "../src/scene/Light.hpp"
#include "../src/scene/Scene.hpp"
#include "../src/platform/GLFWHandler.hpp"
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

    void viewProjection();

    void update();

    void setActiveScene(Scene* scene);

private:
    void applyDirectionalLight();
    void applyPointLights();

    void drawEnemies();
    void drawDynamicObjects();
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
