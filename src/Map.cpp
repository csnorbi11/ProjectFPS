#include <utility>

#include "headers/Map.hpp"

Map::Map(std::string path)
    :
    Model(std::move(path),"basic")
{}

Map::~Map()=default;
