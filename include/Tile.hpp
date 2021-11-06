#ifndef TILE_HPP
#define TILE_HPP

#include "BombCounter.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <array>

class Tile : public sf::Drawable {
public:
  Tile() = default;
  Tile(const sf::Vector2u &coords, sf::Vector2f position, float scale = 1.f);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void set_bomb();
  void click(int bombs_nearby);
  void set_flag(bool mode);
  void set_hover(bool mode);

  bool is_bomb() const;
  bool is_clicked() const;
  bool is_flagged() const;
  bool is_hover() const;

  bool contains(const sf::Vector2f &position) const;
  sf::Vector2u get_position() const;

private:
  void load_sounds();

  sf::Vector2u m_coords;
  BombCounter m_bombs_nearby;

  sf::Sprite m_s_tile, m_s_bomb, m_s_flag;
  sf::Sound m_sound_tile_click, m_sound_bomb_explosion;
  bool m_bomb = false;
  bool m_clicked = false;
  bool m_flagged = false;
  bool m_hover = false;
};

#endif