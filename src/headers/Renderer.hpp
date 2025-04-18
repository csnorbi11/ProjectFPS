#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <unordered_map>
#include <glad/glad.h>
#include <string>
#include <vector>

#include "Light.hpp"


class Map;
class Shader;
class ShaderProgram;
class Model;
class GameObject;
class Camera;

class Renderer {
public:
    Renderer(std::vector<std::unique_ptr<GameObject>>& gameObjects,
        std::vector<std::unique_ptr<Light>>& lights);
    ~Renderer();


    void createShaderProgram(const std::string &name,
                             const std::string &vertexShader, const std::string &fragmentShader);
    void draw();
    void drawMap();
    void update();

    void setActiveCamera(Camera* camera);
    void setActiveMap(Map* map);

private:
    void loadShader(const std::string &path, GLenum shaderType);
    void loadModel(const std::string &path, const std::string &shaderProgName);

    std::unordered_map<std::string, std::unique_ptr<Shader> > shaders = {};
    std::unordered_map<std::string, std::unique_ptr<ShaderProgram> > shaderPrograms = {};
    std::unordered_map<std::string, std::unique_ptr<Model> > models={};

    Map* currentMap=nullptr;

    Camera* camera=nullptr;
    std::string activeShaderProgram={};

    std::vector<std::unique_ptr<GameObject>>& gameObjects;
    std::vector<std::unique_ptr<Light>>& lights;

    bool debugMode=false;

};

#endif //RENDERER_HPP
