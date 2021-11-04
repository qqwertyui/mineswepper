#include "BombCounter.hpp"

BombCounter::BombCounter() {
  font.loadFromFile("arial.ttf");
  text.setFont(font);
  text.setFillColor(sf::Color::Black);
  text.setStyle(sf::Text::Bold);
  text.setCharacterSize(18);
}

void BombCounter::update(int bombs_left, int bombs_total) {
  text.setString(std::to_string(bombs_left) + "/" +
                 std::to_string(bombs_total) + " bombs");
}

void BombCounter::draw(sf::RenderTarget &target,
                       sf::RenderStates states) const {
  target.draw(text);
}