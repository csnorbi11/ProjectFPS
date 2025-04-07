#ifndef GAME_HPP
#define GAME_HPP
#include "GLFWHandler.hpp"


class Game {
public:
  explicit Game(WindowType windowType);
  ~Game();

  void run();

private:
  static std::unique_ptr<WindowHandler> createWindowHandler(WindowType windowType);

  void gameLoop();


  std::unique_ptr<WindowHandler> windowHandler;

  float deltaTime;
  float lastFrameEnd;

};

#endif //GAME_HPP
