#ifndef MESH_HPP
#define MESH_HPP
#include <string>
#include <vector>
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/hash.hpp>

#include "Material.hpp"
#include "Vertex.hpp"





struct Triangle {
	glm::vec3 vertices[3];
    glm::vec3 normal;
};

class Mesh {
public:
    Mesh(std::string name, std::vector<Vertex> vertices, std::vector<uint32_t> indices, Material* material,
        std::vector<Triangle> triangles);
    ~Mesh();

    void setupInstancing(unsigned int instanceVBO);

    void bindVAO() const;
    void unbindVAO() const;

    void changeMaterial(Material* material);

    Material* getMaterial() const;
    const std::vector<uint32_t> &getIndices() const;
    const std::vector<Vertex> &getVertices() const;
    const std::vector<Triangle> &getTriangles() const;
    uint32_t getVAO() const;
    std::string& getName();

private:
    void setupMesh();

    std::vector<Vertex> vertices;
    std::vector<uint32_t> indices;
    Material* material = nullptr;
    std::vector<Triangle> triangles;

    uint32_t VAO{}, VBO{}, EBO{};
    std::string name;

};



#endif //MESH_HPP
