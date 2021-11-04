#include "Game.hpp"

Game::Game()
    : mwindow(sf::VideoMode(480, 480), "Mineswepper", sf::Style::Close),
      map(mwindow.getSize()) {}

void Game::run() {
  sf::Clock clock;
  sf::Time timer;
  const sf::Time TIME_PER_FRAME = sf::seconds(1.f / Game::FPS);
  while (mwindow.isOpen()) {
    timer = sf::Time::Zero;
    while (timer < TIME_PER_FRAME) {
      timer += clock.restart();
    }
    handleEvents();
    update();
    render();
  }
}

void Game::handleEvents() {
  sf::Event event;
  while (mwindow.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      mwindow.close();
    } else if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::Key::Escape) {
        mwindow.close();
      }
    } else if (event.type == sf::Event::MouseButtonPressed) {
      map.click(event.mouseButton.button,
                sf::Vector2u(event.mouseButton.x, event.mouseButton.y));
    }
  }
}

void Game::update() {
  stats.update(map.get_bombs_left(), map.get_bomb_amount());
  if (map.is_game_running()) {
  }
}

void Game::render() {
  mwindow.clear(sf::Color::White);
  mwindow.draw(map);
  mwindow.draw(stats);
  mwindow.display();
}