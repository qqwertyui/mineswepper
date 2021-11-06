#ifndef GAME_HPP
#define GAME_HPP

#include "Board.hpp"
#include "BoardStatus.hpp"
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

  void load_icon();
  void load_resources();

  sf::RenderWindow m_window;
  std::unique_ptr<Board> m_board = nullptr;
  std::unique_ptr<BoardStatus> m_board_status = nullptr;

  static constexpr double FPS = 60.f;
  struct Window {
    static constexpr int WIDTH = 480;
    static constexpr int HEIGHT = 540;
  };
};

#endif