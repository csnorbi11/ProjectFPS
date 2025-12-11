#ifndef VERTEX_HPP
#define VERTEX_HPP

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

#endif // !VERTEX_HPP
