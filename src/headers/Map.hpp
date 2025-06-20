#ifndef MAP_HPP
#define MAP_HPP

#include <vector>
#include <memory>

#include "StaticObject.hpp"

class Map {
public:
    Map();
    ~Map();

private:
    std::vector<StaticObject> objects;
};

#endif //MAP_HPP
