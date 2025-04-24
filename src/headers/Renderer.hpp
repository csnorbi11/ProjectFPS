#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <unordered_map>
#include <glad/glad.h>
#include <string>
#include "Light.hpp"

class Camera;
class Shader;
class ShaderProgram;
class Model;
class Scene;

class Renderer {
public:
    Renderer();
    ~Renderer();


    void createShaderProgram(const std::string &name,
                             const std::string &vertexShader, const std::string &fragmentShader);

    void updateDirectionalLight();

    void drawScene();
    void update();

    void setActiveScene(Scene* scene);

private:
    void drawGameObjects();
    void drawMap();

    void loadShader(const std::string &path, GLenum shaderType);
    void loadModel(const std::string &path, const std::string &shaderProgName);

    std::unordered_map<std::string, std::unique_ptr<Shader> > shaders = {};
    std::unordered_map<std::string, std::unique_ptr<ShaderProgram> > shaderPrograms = {};
    std::unordered_map<std::string, std::unique_ptr<Model> > models={};

    std::string activeShaderProgram={};

    Scene* currentScene=nullptr;

    bool debugMode=false;

};

#endif //RENDERER_HPP
