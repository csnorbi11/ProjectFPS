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
class AssetManager;

//unsigned int TextureFromFile(const char *path, const std::string &directory, bool gamma = false);

class Model {
public:
    explicit Model(std::string path, AssetManager& assetManager);

    ~Model();


    const std::string &getShaderProgName();
    std::vector<std::unique_ptr<Mesh>> &getMeshes();
    const std::string& getPath();



private:
    void loadModel(AssetManager& assetManager);
    void processNode(aiNode *node, const aiScene *scene, AssetManager& assetManager);

    Mesh* processMesh(aiMesh *mesh, const aiScene *scene, AssetManager& assetManager);
    void loadOrGetMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         std::string typeName, AssetManager& assetManager);

    void logModelInfo() const;

    std::string shaderProgName;

    std::vector<Texture> textures_loaded;
    std::vector<std::unique_ptr<Mesh>> meshes;

    std::string directory;
    std::string path;
};

#endif //MODEL_HPP
