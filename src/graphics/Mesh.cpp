#include <utility>

#include "Mesh.hpp"

#include <glad/glad.h>

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<uint32_t> indices,
    std::vector<Texture> textures, std::vector<Triangle> triangles)
    :
    vertices(std::move(vertices)),
    indices(std::move(indices)),
    textures(std::move(textures)),
    triangles(std::move(triangles))
{
    setupMesh();
}

Mesh::~Mesh() {
    glDeleteBuffers(1, &VBO);
    glDeleteVertexArrays(1, &VAO);
}

void Mesh::bindVAO() const {
    glBindVertexArray(VAO);
}

void Mesh::unbindVAO() const {
    glBindVertexArray(0);
}

const std::vector<Texture> & Mesh::getTextures() const {
    return textures;
}

const std::vector<uint32_t> & Mesh::getIndices() const {
    return indices;
}

const std::vector<Vertex> & Mesh::getVertices() const {
    return vertices;
}

const std::vector<Triangle>& Mesh::getTriangles() const
{
	return triangles;
}


void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                 &indices[0], GL_STATIC_DRAW);

    // vertex positions
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), static_cast<void *>(0));
    // vertex normals
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, normal)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2,3,GL_FLOAT,GL_FALSE,
        sizeof(Vertex),reinterpret_cast<void *>(offsetof(Vertex,ambient)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, diffuse)));
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(4, 3, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, specular)));
    // vertex texture coords
    glEnableVertexAttribArray(5);
    glVertexAttribPointer(5, 2, GL_FLOAT, GL_FALSE,
        sizeof(Vertex), reinterpret_cast<void *>(offsetof(Vertex, texCoords)));

    glBindVertexArray(0);
}
