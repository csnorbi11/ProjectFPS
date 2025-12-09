#ifndef MESH_HPP
#define MESH_HPP
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "Material.hpp"

struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
    glm::vec3 tangent;
    
    bool operator==(const Vertex& other) const {
        return position == other.position &&
            normal == other.normal &&
            texCoords == other.texCoords &&
            tangent == other.tangent;
    }
};

namespace std {
    template<> struct hash<Vertex> {
        size_t operator()(Vertex const& vertex) const {

            size_t h1 = hash<glm::vec3>{}(vertex.position);
            size_t h2 = hash<glm::vec3>{}(vertex.normal);
            size_t h3 = hash<glm::vec2>{}(vertex.texCoords);
            size_t h4 = hash<glm::vec3>{}(vertex.tangent);

            return ((h1 ^ (h2 << 1)) >> 1) ^ (h3 << 1) ^ (h4 << 1);
        }
    };
}



struct Triangle {
	glm::vec3 vertices[3];
    glm::vec3 normal;
};

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices, Material* material,
        std::vector<Triangle> triangles);
    ~Mesh();

    void bindVAO() const;
    void unbindVAO() const;

    Material* getMaterial() const;
    const std::vector<uint32_t> &getIndices() const;
    const std::vector<Vertex> &getVertices() const;
    const std::vector<Triangle> &getTriangles() const;
    uint32_t getVAO() const;

private:
    void setupMesh();

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    Material* material = nullptr;
    std::vector<Triangle> triangles;

    uint32_t VAO{}, VBO{}, EBO{};


};



#endif //MESH_HPP
