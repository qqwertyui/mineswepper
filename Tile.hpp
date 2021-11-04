#ifndef TILE_HPP
#define TILE_HPP

#include <SFML/Graphics.hpp>
#include <array>

class Tile : public sf::Drawable {
public:
  Tile() = default;
  Tile(const std::array<sf::Texture *, 5> &textures, const sf::Vector2f &scale);

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

  void set_bomb();
  void click();
  void flag(bool mode);

  bool is_flagged() const;
  bool is_clicked() const;
  bool is_bomb() const;

  bool contains(const sf::Vector2f &position) const;
  void set_position(const sf::Vector2f &position);

private:
  sf::Sprite s_tile, s_bomb, s_flag;
  bool bomb = false;
  bool clicked = false;
  bool flagged = false;

  std::array<sf::Texture *, 5> textures;
  enum TextureId {
    CLICKED = 0,
    UNCLICKED = 1,
    EXPLODED = 2,
    BOMB = 3,
    FLAG = 4
  };
};

#endif