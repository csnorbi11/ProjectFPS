#ifndef GAME_HPP
#define GAME_HPP
#include <chrono>

#include "GameObject.hpp"
#include "GLFWHandler.hpp"

class Camera;
class Renderer;


class Game {
public:
    explicit Game(WindowType windowType);
    ~Game();

    void run();

private:
    static std::unique_ptr<WindowHandler> createWindowHandler(WindowType windowType);


    void gameLoop();
    void calculateDeltaTime();
    void render() const;

    void input() const;

    std::unique_ptr<WindowHandler> windowHandler;
    std::unique_ptr<Renderer> renderer;
    std::vector<std::unique_ptr<GameObject>> gameObjects;
    std::unique_ptr<Camera> camera;

    std::chrono::time_point<std::chrono::system_clock> frameStart={};
    std::chrono::time_point<std::chrono::system_clock> frameEnd={};
    long frameDuration=0;
    double deltaTime=0;
};

#endif //GAME_HPP
