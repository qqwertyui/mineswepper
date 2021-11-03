#include "Game.hpp"

Game::Game()
    : mwindow(sf::VideoMode(480, 480), "Mineswepper", sf::Style::Close),
      map(sf::Vector2u(480, 480)) {}

void Game::run() {
  while (mwindow.isOpen()) {
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
      map.update(sf::Vector2u(event.mouseButton.x, event.mouseButton.y));
    }
  }
}

void Game::update() {}

void Game::render() {
  mwindow.clear(sf::Color::White);
  mwindow.draw(map);
  mwindow.display();
}