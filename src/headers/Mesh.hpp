#ifndef MESH_HPP
#define MESH_HPP
#include <string>
#include <unordered_map>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

struct Texture {
    uint32_t id;
    std::string type;
    std::string path;
};

class Mesh {
public:
    Mesh(std::unordered_map<Vertex,uint32_t> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures);
    ~Mesh();

    void bindVAO() const;
    void unbindVAO() const;

    const std::vector<Texture> &getTextures() const;
    const std::vector<uint32_t> &getIndices() const;
    const std::unordered_map<Vertex,uint32_t> &getVertices() const;

private:
    void setupMesh();

    std::unordered_map<Vertex,uint32_t> vertices;
    std::vector<uint32_t> indices;
    std::vector<Texture> textures;

    uint32_t VAO{}, VBO{}, EBO{};


};



#endif //MESH_HPP
