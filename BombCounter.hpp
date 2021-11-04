#ifndef BOMBCOUNTER_HPP
#define BOMBCOUNTER_HPP

#include <SFML/Graphics.hpp>

class BombCounter : public sf::Drawable {
public:
  BombCounter();

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  void update(int bombs_left, int bombs_total);

private:
  sf::Font font;
  sf::Text text;
};

#endif