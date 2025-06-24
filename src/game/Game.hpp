#ifndef GAME_HPP
#define GAME_HPP
#include <chrono>

#include "../platform/GLFWHandler.hpp"
#include "../platform/GLFWInput.hpp"
#include "../graphics/Renderer.hpp"
#include "../scene/Scene.hpp"


class Game {
public:
    explicit Game();
    ~Game();

    void run();

private:
    void gameLoop();
    void calculateDeltaTime();
    void render() const;

    void input();

    std::unique_ptr<GLFWHandler> glfwHandler;
	std::unique_ptr<GLFWInput> glfwInput;
    std::unique_ptr<Renderer> renderer;
    std::unique_ptr<Scene> scene;
    std::unique_ptr<AssetManager> assetManager;


    std::chrono::steady_clock::time_point frameStart={};
    std::chrono::steady_clock::time_point frameEnd={};
    long frameDuration=0;
    double deltaTime=0;

};

#endif //GAME_HPP
