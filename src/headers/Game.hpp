#ifndef GAME_HPP
#define GAME_HPP
#include "GLFWHandler.hpp"


class Game {
public:
  Game(WindowType windowType);
  ~Game();

  void run() const;

private:
  static std::unique_ptr<WindowHandler> createWindowHandler(WindowType windowType);


  void gameLoop() const;


  std::unique_ptr<WindowHandler> windowHandler;

};

#endif //GAME_HPP
