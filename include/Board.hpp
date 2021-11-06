#ifndef BOARD_HPP
#define BOARD_HPP

#include <SFML/Graphics.hpp>
#include <vector>

#include "Tile.hpp"

class Board : public sf::Drawable {
public:
  Board(const sf::IntRect &board);
  Board() = delete;

  void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
  void click(sf::Mouse::Button button, sf::Vector2u clickPosition);
  void update();
  void reset();

  bool is_board_active() const;

  void highlight_active_tile(const sf::Vector2u &mouse_position);

  int get_bombs_left() const;
  int get_bombs_number() const;

private:
  static constexpr double DEFAULT_COVERAGE = 0.20f;
  static constexpr unsigned int SQUARE_SIZE = 20;

  sf::IntRect m_global_position;
  float m_tile_size;

  Tile m_tiles[Board::SQUARE_SIZE][Board::SQUARE_SIZE];
  Tile *m_last_highlighted_tile = nullptr;

  float m_scale_factor;
  bool m_board_active = true;

  Tile *find_tile_by_position(const sf::Vector2u &position);
  std::vector<sf::Vector2u> generate_bombs();
  int get_flagged_tiles() const;
  int get_unclicked_tiles() const;

  void uncover_empty_tiles(Tile &current);
  int count_bombs_nearby(Tile &tile);

  void detonate_all_bombs();

  // remove those
  [[deprecated]] void lose_game();
  [[deprecated]] void win_game();

  Tile *get_top_tile(Tile &tile);
  Tile *get_right_tile(Tile &tile);
  Tile *get_bottom_tile(Tile &tile);
  Tile *get_left_tile(Tile &tile);
  std::array<Tile *, 8> get_sides(Tile &current);
};

#endif