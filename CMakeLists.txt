cmake_minimum_required(VERSION 3.30)
project(ProjectFPS)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

source_group(TREE ${CMAKE_SOURCE_DIR}/src FILES ${SOURCES})


add_executable(ProjectFPS ${SOURCES})
target_include_directories(ProjectFPS PRIVATE 
	${CMAKE_SOURCE_DIR}/lib/include ${CMAKE_SOURCE_DIR}/src)

#add_library(glad "${CMAKE_SOURCE_DIR}/lib/src/glad.c")
#target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/lib/include)


find_package(glfw3 CONFIG REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp REQUIRED)
target_link_libraries(ProjectFPS PRIVATE glfw glad::glad assimp::assimp)



set(SHADERS_DIR ${CMAKE_SOURCE_DIR}/assets/shaders)
set(BUILD_SHADERS_DIR ${CMAKE_BINARY_DIR}/assets/shaders)
file(MAKE_DIRECTORY ${ASSETS_DIR})

add_custom_command(
        TARGET ProjectFPS POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADERS_DIR} ${BUILD_SHADERS_DIR}
        COMMENT "Copying shaders to build directory"
)

set(MODELS_DIR ${CMAKE_SOURCE_DIR}/assets/models)
set(BUILD_MODELS_DIR ${CMAKE_BINARY_DIR}/assets/models)
file(MAKE_DIRECTORY ${ASSETS_DIR})

add_custom_command(
        TARGET ProjectFPS POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${MODELS_DIR} ${BUILD_MODELS_DIR}
        COMMENT "Copying models to build directory"
)