#ifndef MINEFIELD_HPP
#define MINEFIELD_HPP

#include <SFML/Graphics.hpp>
#include <functional>
#include <vector>

#include "Tile.hpp"

class Minefield : public sf::Drawable {
public:
  Minefield(const sf::Vector2u &windowSize);
  Minefield() = delete;
  ~Minefield() = default;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  void click(sf::Mouse::Button button, sf::Vector2u clickPosition);
  void update();

  bool is_game_running() const;
  int get_bombs_left() const;
  int get_bomb_amount() const;
  int get_flagged_tiles() const;

private:
  bool game_running = true;
  unsigned int bomb_amount;

  static constexpr unsigned int SQUARE_SIZE = 10;
  Tile tiles[Minefield::SQUARE_SIZE][Minefield::SQUARE_SIZE];
  sf::Texture txt_tile_clicked, txt_tile_unclicked, txt_tile_exploded, txt_bomb,
      txt_flag;

  sf::Vector2f scale_factor;
  sf::Vector2u tile_size;

  Tile *find_tile_by_position(const sf::Vector2u &position);
  std::vector<sf::Vector2u> generate_bombs();
  void load_textures();
  void initialize_field();

  static constexpr const char *PATH_CLICKED = "assets/tile_clicked.png";
  static constexpr const char *PATH_UNCLICKED = "assets/tile_unclicked.png";
  static constexpr const char *PATH_EXPLODED = "assets/tile_exploded.png";
  static constexpr const char *PATH_BOMB = "assets/bomb.png";
  static constexpr const char *PATH_FLAG = "assets/flag.png";

  static constexpr double DEFAULT_COVERAGE = 0.2;
};

#endif