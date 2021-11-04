#ifndef GAME_HPP
#define GAME_HPP

#include "BombCounter.hpp"
#include "Minefield.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>


class Game : public sf::NonCopyable {
public:
  Game();
  void run();

private:
  void update();
  void handleEvents();
  void render();

  sf::RenderWindow mwindow;
  Minefield map;
  BombCounter stats;

  static constexpr double FPS = 60.f;
};

#endif