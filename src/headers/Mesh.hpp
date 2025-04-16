#ifndef MESH_HPP
#define MESH_HPP
#include <string>
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
    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures);
    Mesh(Mesh&& other)noexcept;
    ~Mesh();

    void bindVAO() const;
    void unbindVAO() const;

    const std::vector<Texture> &getTextures() const;
    const std::vector<uint32_t> &getIndices() const;
    const std::vector<Vertex> &getVertices() const;

    Mesh& operator=(Mesh&&) noexcept;

private:
    void setupMesh();

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<Texture> textures;

    uint32_t VAO{}, VBO{}, EBO{};


};



#endif //MESH_HPP
