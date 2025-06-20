#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"

class ShaderProgram;


unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model {
public:
    explicit Model(std::string path, std::string shaderProgName);

    ~Model();


    const std::string &getShaderProgName();
    std::vector<std::unique_ptr<Mesh>> &getMeshes();




private:
    void loadModel();
    void processNode(aiNode *node, const aiScene *scene);

    Mesh* processMesh(aiMesh *mesh, const aiScene *scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         std::string typeName);

    void logModelInfo() const;

    std::string shaderProgName;

    std::vector<Texture> textures_loaded;
    std::vector<std::unique_ptr<Mesh>> meshes;

    std::string directory;
    std::string path;
};

#endif //MODEL_HPP
