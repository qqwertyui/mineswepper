#include "Minefield.hpp"
#include <chrono>
#include <cstdio>
#include <iostream>
#include <random>
#include <stdexcept>

Minefield::Minefield(const sf::Vector2u &windowSize) {
  this->load_textures();
  this->tile_size = windowSize / Minefield::SQUARE_SIZE;
  this->scale_factor = sf::Vector2f(
      (double)tile_size.x / (double)this->txt_tile_clicked.getSize().x,
      (double)tile_size.y / (double)this->txt_tile_clicked.getSize().y);

  this->initialize_field();
}

void Minefield::initialize_field() {
  std::array<sf::Texture *, 5> textures = {
      &txt_tile_clicked, &txt_tile_unclicked, &txt_tile_exploded, &txt_bomb,
      &txt_flag};

  std::vector<sf::Vector2u> bombs = this->generate_bombs();

  for (unsigned int y = 0; y < Minefield::SQUARE_SIZE; y++) {
    for (unsigned int x = 0; x < Minefield::SQUARE_SIZE; x++) {
      this->tiles[y][x] = Tile(textures, this->scale_factor);
      sf::Vector2u current_position = {x, y};
      auto it = std::find(bombs.begin(), bombs.end(), current_position);
      if (it != bombs.end()) {
        this->tiles[y][x].set_bomb();
      }
    }
  }

  sf::Vector2f position = {0, 0};
  for (unsigned int y = 0; y < Minefield::SQUARE_SIZE; y++) {
    for (unsigned int x = 0; x < Minefield::SQUARE_SIZE; x++) {
      this->tiles[y][x].set_position(position);
      position.x += tile_size.x;
    }
    position.y += tile_size.y;
    position.x = 0;
  }
}

void Minefield::click(sf::Mouse::Button button, sf::Vector2u clickPosition) {
  Tile *tile = this->find_tile_by_position(clickPosition);
  if (tile == nullptr) {
    return;
  }
  if (button == sf::Mouse::Button::Left) {
    tile->click();
    if (tile->is_bomb()) {
      this->game_running = false;
    } else {
      //
    }
  } else if (button == sf::Mouse::Button::Right) {
    if (tile->is_clicked() == false) {
      if (tile->is_flagged() == false) {
        if (this->get_flagged_tiles() != this->get_bomb_amount()) {
          tile->flag(true);
        }
      } else {
        tile->flag(false);
      }
    }
  }
}

Tile *Minefield::find_tile_by_position(const sf::Vector2u &position) {
  sf::Vector2f f_position(position.x, position.y);
  for (unsigned int y = 0; y < Minefield::SQUARE_SIZE; y++) {
    for (unsigned int x = 0; x < Minefield::SQUARE_SIZE; x++) {
      Tile &tile = this->tiles[y][x];
      if (tile.contains(f_position)) {
        return &tile;
      }
    }
  }
  return nullptr;
}

void Minefield::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  for (unsigned int y = 0; y < Minefield::SQUARE_SIZE; y++) {
    for (unsigned int x = 0; x < Minefield::SQUARE_SIZE; x++) {
      target.draw(this->tiles[y][x], states);
    }
  }
}

void Minefield::load_textures() {
  this->txt_tile_clicked.loadFromFile(Minefield::PATH_CLICKED);
  this->txt_tile_unclicked.loadFromFile(Minefield::PATH_UNCLICKED);
  this->txt_bomb.loadFromFile(Minefield::PATH_BOMB);
  this->txt_flag.loadFromFile(Minefield::PATH_FLAG);
  this->txt_tile_exploded.loadFromFile(Minefield::PATH_EXPLODED);
}

std::vector<sf::Vector2u> Minefield::generate_bombs() {
  std::vector<sf::Vector2u> result;
  const int total_fields = Minefield::SQUARE_SIZE * Minefield::SQUARE_SIZE;
  const int needed_fields =
      Minefield::DEFAULT_COVERAGE * static_cast<double>(total_fields);
  std::uniform_int_distribution<unsigned int> wrapper(
      0, Minefield::SQUARE_SIZE - 1);
  std::mt19937 rng(std::chrono::system_clock::now().time_since_epoch().count());
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

int Minefield::get_bombs_left() const {
  return (this->get_bomb_amount() - this->get_flagged_tiles());
}

int Minefield::get_flagged_tiles() const {
  int flags = 0;
  for (unsigned int y = 0; y < Minefield::SQUARE_SIZE; y++) {
    for (unsigned int x = 0; x < Minefield::SQUARE_SIZE; x++) {
      if (this->tiles[y][x].is_flagged()) {
        flags += 1;
      }
    }
  }
  return flags;
}

int Minefield::get_bomb_amount() const {
  int bombs = 0;
  for (unsigned int y = 0; y < Minefield::SQUARE_SIZE; y++) {
    for (unsigned int x = 0; x < Minefield::SQUARE_SIZE; x++) {
      if (this->tiles[y][x].is_bomb()) {
        bombs += 1;
      }
    }
  }
  return bombs;
}

bool Minefield::is_game_running() const { return this->game_running; }