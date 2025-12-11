#ifndef TEXTURE_HPP
#define TEXTURE_HPP

struct Texture {
    const uint32_t id;
    const std::string type;
    const std::string name;
    const std::string path;

    Texture() = delete;
    Texture(const std::string& name, const std::string& path, const uint32_t id, const std::string& type)
        :
        id(id),
        type(type),
        name(name),
        path(path)
    {
    }
    ~Texture() {

    }
};

#endif // !TEXTURE_HPP
