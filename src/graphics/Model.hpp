#ifndef MODEL_HPP
#define MODEL_HPP

#include <memory>
#include <string>
#include <vector>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "Vertex.hpp"

class ShaderProgram;
class AssetManager;
class Texture;


class Model {
public:
    explicit Model(std::string path, AssetManager& assetManager);

    ~Model();


    std::vector<std::unique_ptr<Mesh>> &getMeshes();
    const std::string& getName();



private:
    void loadModel(AssetManager& assetManager);
    void processNode(aiNode *node, const aiScene *scene, AssetManager& assetManager);

    Mesh* processMesh(aiMesh *mesh, const aiScene *scene, AssetManager& assetManager);
    Texture* loadOrGetMaterialTextures(aiMaterial *mat, aiTextureType type,
                                         std::string typeName, AssetManager& assetManager);

    void logModelInfo() const;

    std::vector<Texture> textures_loaded;
    std::vector<std::unique_ptr<Mesh>> meshes;

    std::string directory;
    std::string fullPath;
    std::string name;
};

#endif //MODEL_HPP
