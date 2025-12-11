#include <utility>
#include <iostream>
#include <stdexcept>


#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>


#include "Model.hpp"
#include "Material.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <unordered_map>

#include "game/AssetManager.hpp"
#include "Mesh.hpp"

Model::Model(std::string path, AssetManager& assetManager)
    :
    fullPath(std::move(path)) {
    name = fullPath.substr(fullPath.find_last_of('/')+1);
    loadModel(assetManager);
}

Model::~Model() = default;


std::vector<std::unique_ptr<Mesh>> & Model::getMeshes() {
    return meshes;
}

const std::string& Model::getName()
{
    return name;
}


void Model::logModelInfo() const {
    std::cout << "Model infos:" << std::endl;
    std::cout<<"\tpath: "<<fullPath<<std::endl;
    std::cout<<"\tmeshes count: "<<meshes.size()<<std::endl;
    uint32_t totalVertices = 0;
    for (auto& mesh:meshes) {
        totalVertices += mesh->getVertices().size();
        std::cout<<"\t\tvertices count: "<<mesh->getVertices().size()<<std::endl;
    }
    std::cout<<"\ttotal vertices: "<<totalVertices<<std::endl;
    std::cout<<"models size: "<<static_cast<float>(totalVertices*sizeof(Vertex))/1000.f/1000.f<<"MB"<<std::endl;
}

void Model::loadModel(AssetManager& assetManager) {

    Assimp::Importer import;

    import.SetPropertyFloat(AI_CONFIG_PP_GSN_MAX_SMOOTHING_ANGLE, 80.0f);
    const aiScene* scene = import.ReadFile(fullPath,
        aiProcess_Triangulate |
        aiProcess_FlipUVs |
        aiProcess_JoinIdenticalVertices | // <--- EZT ADD HOZZÁ (Fontos a sorrend: először join, aztán smooth)
        aiProcess_GenSmoothNormals |
        aiProcess_CalcTangentSpace |
        aiProcess_OptimizeMeshes);

    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        std::cerr << "ASSIMP ERROR: " <<
            static_cast<std::string>(import.GetErrorString()) << std::endl;;
        return;
    }
    directory = fullPath.substr(0, fullPath.find_last_of('/'));

    processNode(scene->mRootNode, scene, assetManager);
}

void Model::processNode(aiNode *node, const aiScene *scene, AssetManager& assetManager) {
    // process each mesh located at the current node
    for(unsigned int i = 0; i < node->mNumMeshes; i++)
    {
        // the node object only contains indices to index the actual objects in the scene.
        // the scene contains all the data, node is just to keep stuff organized (like relations between nodes).
        aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
        meshes.emplace_back(std::unique_ptr<Mesh>(processMesh(mesh, scene, assetManager)));
    }
    // after we've processed all of the meshes (if any) we then recursively process each of the children nodes
    for(unsigned int i = 0; i < node->mNumChildren; i++)
    {
        processNode(node->mChildren[i], scene, assetManager);
    }
}

Mesh* Model::processMesh(aiMesh *mesh, const aiScene *scene, AssetManager& assetManager) {
    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<Triangle> triangles;

    for(unsigned int i = 0; i < mesh->mNumVertices; i++)
    {
        Vertex vertex;
        glm::vec3 vector; // we declare a placeholder vector since assimp uses its own vector class that doesn't directly convert to glm's vec3 class so we transfer the data to this placeholder glm::vec3 first.
        // positions
        vector.x = mesh->mVertices[i].x;
        vector.y = mesh->mVertices[i].y;
        vector.z = mesh->mVertices[i].z;
        vertex.position = vector;
        // normals
        if (mesh->HasNormals())
        {
            vector.x = mesh->mNormals[i].x;
            vector.y = mesh->mNormals[i].y;
            vector.z = mesh->mNormals[i].z;
            vertex.normal = vector;
        }
        // texture coordinates
        if(mesh->mTextureCoords[0]) // does the mesh contain texture coordinates?
        {
            glm::vec2 vec;
            // a vertex can contain up to 8 different texture coordinates. We thus make the assumption that we won't
            // use models where a vertex can have multiple texture coordinates so we always take the first set (0).
            vec.x = mesh->mTextureCoords[0][i].x;
            vec.y = mesh->mTextureCoords[0][i].y;
            vertex.texCoords = vec;
        }
        else
            vertex.texCoords = glm::vec2(0.0f, 0.0f);

        if (mesh->HasTangentsAndBitangents()) {
            glm::vec3 vec;
            vec.x = mesh->mTangents[i].x;
            vec.y = mesh->mTangents[i].y;
            vec.z = mesh->mTangents[i].z;
        }
        else {
            vertex.tangent = glm::vec3{ 0.f };
        }

        vertices.push_back(vertex);
    }
    for (unsigned int i = 0; i < mesh->mNumFaces; i++)
    {
        aiFace face = mesh->mFaces[i];
        

        // Mivel aiProcess_Triangulate-et használunk, tudjuk, hogy mindig 3 index van.
        // Nem kell belső ciklus, sem if feltétel.

        // 1. Indexek mentése a rendereléshez
        indices.push_back(face.mIndices[0]);
        indices.push_back(face.mIndices[1]);
        indices.push_back(face.mIndices[2]);

        // 2. Fizikai háromszög (vagy Raycast) adatok kinyerése
        glm::vec3 a = vertices[face.mIndices[0]].position;
        glm::vec3 b = vertices[face.mIndices[1]].position;
        glm::vec3 c = vertices[face.mIndices[2]].position;

        // Normálvektor számítás (Geometriai normál)
        glm::vec3 ab = b - a;
        glm::vec3 ac = c - a;
        glm::vec3 normal = glm::normalize(glm::cross(ab, ac));

        triangles.push_back(Triangle{ a, b, c, normal });
    }


    // process materials
    aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];
    // we assume a convention for sampler names in the shaders. Each diffuse texture should be named
    // as 'texture_diffuseN' where N is a sequential number ranging from 1 to MAX_SAMPLER_NUMBER.
    // Same applies to other texture as the following list summarizes:
    // diffuse: texture_diffuseN
    // specular: texture_specularN
    // normal: texture_normalN
    std::string matName = name+"."+material->GetName().C_Str();
    if (assetManager.getMaterials().count(matName) != 0) {
        return new Mesh(vertices, indices, assetManager.getMaterials()[matName].get(), triangles);
    }

    MaterialParam matParam{};
    float shininess,shininessStrength, specularExponent;
    aiColor3D ambientColor,diffuseColor,specularColor;
 
    if(material->Get(AI_MATKEY_COLOR_AMBIENT, ambientColor)==AI_SUCCESS)
        matParam.ambient = glm::vec3(ambientColor.r, ambientColor.g, ambientColor.b);
    if (material->Get(AI_MATKEY_COLOR_DIFFUSE, diffuseColor) == AI_SUCCESS)
        matParam.diffuse = glm::vec3(diffuseColor.r, diffuseColor.g, diffuseColor.b);
    if (material->Get(AI_MATKEY_COLOR_SPECULAR, specularColor) == AI_SUCCESS)
        matParam.specular = glm::vec3(specularColor.r, specularColor.g, specularColor.b);
    if (material->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS) 
        matParam.shininess = shininess;
    if (glm::length(matParam.ambient) < 0.01f && glm::length(matParam.diffuse) > 0.01f) {
        matParam.ambient = matParam.diffuse;
    }

    Texture* diffuseMap = nullptr;
    Texture* specularMap = nullptr;

    if (material->GetTextureCount(aiTextureType_DIFFUSE) > 0) {
        diffuseMap = loadOrGetMaterialTextures(material, aiTextureType_DIFFUSE, "texture_diffuse", assetManager);
    }
    if (material->GetTextureCount(aiTextureType_SPECULAR) > 0) {
        specularMap = loadOrGetMaterialTextures(material, aiTextureType_SPECULAR, "texture_specular", assetManager);
    }
    

    assetManager.createMaterial(matName, "lit", matParam, {diffuseMap,specularMap});

    return new Mesh(vertices, indices,assetManager.getMaterials()[matName].get(), triangles);
}

Texture* Model::loadOrGetMaterialTextures(aiMaterial *mat, aiTextureType type, std::string typeName, AssetManager& assetManager) {

        
        aiString str;
        mat->GetTexture(type, 0, &str);
        std::string fPath = directory+"/"+ str.C_Str();

        if (assetManager.getTextures().count(name) == 0) {
            assetManager.loadTexture(str.C_Str(), fPath, typeName);
        }
        return assetManager.getTextures()[str.C_Str()].get();
}
