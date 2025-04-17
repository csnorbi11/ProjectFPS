#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <unordered_map>
#include <glad/glad.h>
#include <string>


class Map;
class Shader;
class ShaderProgram;
class Model;
class GameObject;
class Camera;

class Renderer {
public:
    Renderer();
    ~Renderer();


    void createShaderProgram(const std::string &name,
                             const std::string &vertexShader, const std::string &fragmentShader);
    void draw(const GameObject &gameObject);
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

    bool debugMode=false;

};

#endif //RENDERER_HPP
