#ifndef MESH_HPP
#define MESH_HPP
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec3 ambient = { 1,1,1 }, diffuse = { 1,1,1 }, specular = { 1,1,1 };
    glm::vec2 texCoords;
    
    bool operator==(const Vertex& other) const {
        return position == other.position && normal == other.normal && texCoords == other.texCoords;
    }
};

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {
            return ((hash<glm::vec3>()(vertex.position) ^
                   (hash<glm::vec3>()(vertex.normal) << 1)) >> 1) ^
                   (hash<glm::vec2>()(vertex.texCoords) << 1);
        }
    };
}

struct Texture {
    uint32_t id;
    std::string type;
    std::string path;
};

struct Triangle {
	glm::vec3 vertices[3];
    glm::vec3 normal;
};

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, std::vector<Texture> textures,
        std::vector<Triangle> triangles);
    ~Mesh();

    void bindVAO() const;
    void unbindVAO() const;

    const std::vector<Texture> &getTextures() const;
    const std::vector<uint32_t> &getIndices() const;
    const std::vector<Vertex> &getVertices() const;
    const std::vector<Triangle> &getTriangles() const;

private:
    void setupMesh();

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    std::vector<Texture> textures;
    std::vector<Triangle> triangles;

    uint32_t VAO{}, VBO{}, EBO{};


};



#endif //MESH_HPP
