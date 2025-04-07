#ifndef GAME_HPP
#define GAME_HPP
#include <chrono>

#include "GLFWHandler.hpp"


class Game {
public:
  explicit Game(WindowType windowType);
  ~Game();

  void run();

private:
  static std::unique_ptr<WindowHandler> createWindowHandler(WindowType windowType);



  void gameLoop();
  void calculateDeltaTime();
  void render();

  std::unique_ptr<WindowHandler> windowHandler;

  std::chrono::time_point<std::chrono::system_clock> frameStart;
  std::chrono::time_point<std::chrono::system_clock> frameEnd;
  long frameDuration;
  double deltaTime;
};

#endif //GAME_HPP
