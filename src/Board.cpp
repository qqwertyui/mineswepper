#include "Board.hpp"
#include "ResourceHolder.hpp"
#include <chrono>
#include <random>

Board::Board(const sf::IntRect &board) {
  m_tile_size = (float)board.width / (float)Board::SQUARE_SIZE;
  sf::Texture *txt_tile_unclicked =
      TextureHolder::get(Textures::TILE_UNCLICKED);
  m_scale_factor =
      (double)m_tile_size / (double)txt_tile_unclicked->getSize().x;

  m_global_position = board;
  reset();
}

void Board::reset() {
  std::vector<sf::Vector2u> bombs = generate_bombs();
  for (auto x = 0; x < Board::SQUARE_SIZE; x++) {
    for (auto y = 0; y < Board::SQUARE_SIZE; y++) {
      sf::Vector2f tile_global_position = {
          x * m_tile_size + m_global_position.left,
          y * m_tile_size + m_global_position.top};
      m_tiles[x][y] =
          Tile(sf::Vector2u(x, y), tile_global_position, m_scale_factor);
      auto it = std::find(bombs.begin(), bombs.end(), sf::Vector2u(x, y));
      if (it != bombs.end()) {
        m_tiles[x][y].set_bomb();
      }
    }
  }
  m_board_active = true;
}

void Board::lose_game() {
  detonate_all_bombs();
  m_board_active = false;
}

void Board::win_game() { m_board_active = false; }

void Board::detonate_all_bombs() {
  for (auto x = 0; x < Board::SQUARE_SIZE; x++) {
    for (auto y = 0; y < Board::SQUARE_SIZE; y++) {
      Tile &current = m_tiles[x][y];
      if (current.is_bomb() == true && current.is_clicked() == false) {
        current.click(0);
      }
    }
  }
}

void Board::click(sf::Mouse::Button button, sf::Vector2u clickPosition) {
  if (m_board_active == false) {
    return;
  }

  Tile *tile = find_tile_by_position(clickPosition);
  if (tile == nullptr) {
    return;
  }
  if (button == sf::Mouse::Button::Left) {
    if (tile->is_flagged() == false) {
      tile->click(count_bombs_nearby(*tile));
      if (tile->is_bomb()) {
        lose_game();
      } else {
        uncover_empty_tiles(*tile);
      }
    }
  } else if (button == sf::Mouse::Button::Right) {
    if (tile->is_clicked() == false) {
      if (tile->is_flagged() == false) {
        if (get_flagged_tiles() != get_bombs_number()) {
          tile->set_flag(true);
        }
      } else {
        tile->set_flag(false);
      }
    }
  }
}

void Board::update() {
  if (get_unclicked_tiles() == get_bombs_number()) {
    win_game();
  }
}

void Board::highlight_active_tile(const sf::Vector2u &mouse_position) {
  if (m_last_highlighted_tile) {
    m_last_highlighted_tile->set_hover(false);
  }
  Tile *tile = find_tile_by_position(mouse_position);
  if (tile == nullptr) {
    return;
  }
  tile->set_hover(true);
  m_last_highlighted_tile = tile;
}

int Board::get_unclicked_tiles() const {
  int unclicked = 0;
  for (auto x = 0; x < Board::SQUARE_SIZE; x++) {
    for (auto y = 0; y < Board::SQUARE_SIZE; y++) {
      const Tile &tile = m_tiles[x][y];
      if (tile.is_clicked() == false) {
        unclicked += 1;
      }
    }
  }
  return unclicked;
}

Tile *Board::find_tile_by_position(const sf::Vector2u &position) {
  sf::Vector2f f_position(position.x, position.y);
  for (auto x = 0; x < Board::SQUARE_SIZE; x++) {
    for (auto y = 0; y < Board::SQUARE_SIZE; y++) {
      Tile &tile = m_tiles[x][y];
      if (tile.contains(f_position)) {
        return &tile;
      }
    }
  }
  return nullptr;
}

void Board::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (auto x = 0; x < Board::SQUARE_SIZE; x++) {
    for (auto y = 0; y < Board::SQUARE_SIZE; y++) {
      target.draw(m_tiles[x][y], states);
    }
  }
}

std::vector<sf::Vector2u> Board::generate_bombs() {
  const int total_fields = Board::SQUARE_SIZE * Board::SQUARE_SIZE;
  const int needed_fields =
      Board::DEFAULT_COVERAGE * static_cast<double>(total_fields);
  std::uniform_int_distribution<unsigned int> wrapper(0,
                                                      Board::SQUARE_SIZE - 1);
  std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
  std::vector<sf::Vector2u> result;
  for (int i = 0; i < needed_fields;) {
    sf::Vector2u t = {wrapper(rng), wrapper(rng)};
    auto it =
        std::find_if(result.begin(), result.end(), [&t](sf::Vector2u current) {
          return (t.x == current.x && t.y == current.y) ? true : false;
        });
    if (it == result.end()) {
      result.push_back(t);
      i += 1;
    }
  }
  return result;
}

int Board::get_bombs_left() const {
  return (get_bombs_number() - get_flagged_tiles());
}

int Board::get_flagged_tiles() const {
  int flags = 0;
  for (auto x = 0; x < Board::SQUARE_SIZE; x++) {
    for (auto y = 0; y < Board::SQUARE_SIZE; y++) {
      if (m_tiles[x][y].is_flagged()) {
        flags += 1;
      }
    }
  }
  return flags;
}

int Board::get_bombs_number() const {
  int bombs = 0;
  for (auto x = 0; x < Board::SQUARE_SIZE; x++) {
    for (auto y = 0; y < Board::SQUARE_SIZE; y++) {
      if (m_tiles[x][y].is_bomb()) {
        bombs += 1;
      }
    }
  }
  return bombs;
}

bool Board::is_board_active() const { return m_board_active; }

Tile *Board::get_top_tile(Tile &tile) {
  sf::Vector2u pos = tile.get_position();
  if (pos.y > 0) {
    return &m_tiles[pos.x][pos.y - 1];
  }
  return nullptr;
}

Tile *Board::get_right_tile(Tile &tile) {
  sf::Vector2u pos = tile.get_position();
  if (pos.x < (SQUARE_SIZE - 1)) {
    return &m_tiles[pos.x + 1][pos.y];
  }
  return nullptr;
}

Tile *Board::get_bottom_tile(Tile &tile) {
  sf::Vector2u pos = tile.get_position();
  if (pos.y < (SQUARE_SIZE - 1)) {
    return &m_tiles[pos.x][pos.y + 1];
  }
  return nullptr;
}

Tile *Board::get_left_tile(Tile &current) {
  sf::Vector2u pos = current.get_position();
  if (pos.x > 0) {
    return &m_tiles[pos.x - 1][pos.y];
  }
  return nullptr;
}

int Board::count_bombs_nearby(Tile &current) {
  std::array<Tile *, 8> sides = get_sides(current);
  int result = 0;
  for (Tile *t : sides) {
    if (t) {
      result += (t->is_bomb()) ? 1 : 0;
    }
  }
  return result;
}

void Board::uncover_empty_tiles(Tile &current) {
  if (count_bombs_nearby(current) != 0) {
    return;
  }

  std::array<Tile *, 8> sides = get_sides(current);
  for (Tile *t : sides) {
    if (t) {
      if (t->is_clicked() == false) {
        t->click(count_bombs_nearby(*t));
        uncover_empty_tiles(*t);
      }
    }
  }
}

std::array<Tile *, 8> Board::get_sides(Tile &current) {
  Tile *top = get_top_tile(current);
  Tile *right = get_right_tile(current);
  Tile *bottom = get_bottom_tile(current);
  Tile *left = get_left_tile(current);

  Tile *topleft = (top && left) ? get_left_tile(*top) : nullptr;
  Tile *bottomleft = (bottom && left) ? get_left_tile(*bottom) : nullptr;
  Tile *topright = (top && right) ? get_right_tile(*top) : nullptr;
  Tile *bottomright = (bottom && right) ? get_right_tile(*bottom) : nullptr;

  std::array<Tile *, 8> sides = {top,    topright,   right, bottomright,
                                 bottom, bottomleft, left,  topleft};
  return sides;
}