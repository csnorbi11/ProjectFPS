cmake_minimum_required(VERSION 3.30)
project(ProjectFPS_BSP)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

add_executable(ProjectFPS_BSP ${SOURCES} ${HEADERS})
set(CMAKE_TOOLCHAIN_FILE "C:/Users/Norbi/vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake" CACHE STRING "")

if (WIN32)
    set(CMAKE_C_COMPILER clang-cl)
    set(CMAKE_CXX_COMPILER clang-cl)
else()
    set(CMAKE_C_COMPILER clang)
    set(CMAKE_CXX_COMPILER clang++)
endif()

find_package(glfw3 REQUIRED)
find_package(glad CONFIG REQUIRED)
find_package(glm CONFIG REQUIRED)
find_package(assimp REQUIRED)



include_directories(glad PUBLIC "C:/Users/Norbi/vcpkg/vcpkg/installed/x64-windows/include")
add_library(glad STATIC "src/glad.c")
target_link_libraries(ProjectFPS_BSP PRIVATE glfw glad assimp::assimp)


set(SHADERS_DIR ${CMAKE_SOURCE_DIR}/assets/shaders)
set(BUILD_SHADERS_DIR ${CMAKE_BINARY_DIR}/assets/shaders)
file(MAKE_DIRECTORY ${ASSETS_DIR})

add_custom_command(
        TARGET ProjectFPS_BSP POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${SHADERS_DIR} ${BUILD_SHADERS_DIR}
        COMMENT "Copying shaders to build directory"
)

set(MODELS_DIR ${CMAKE_SOURCE_DIR}/assets/models)
set(BUILD_MODELS_DIR ${CMAKE_BINARY_DIR}/assets/models)
file(MAKE_DIRECTORY ${ASSETS_DIR})

add_custom_command(
        TARGET ProjectFPS_BSP POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ${MODELS_DIR} ${BUILD_MODELS_DIR}
        COMMENT "Copying models to build directory"
)