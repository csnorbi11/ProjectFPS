#ifndef RENDERCOMMAND_HPP
#define RENDERCOMMAND_HPP

struct RenderCommand {
    const std::string* modelPath;
    Mesh* mesh;
    Material* material;
    glm::mat4 transform;
};

#endif // !RENDERCOMMAND_HPP
