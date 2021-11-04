#include "Tile.hpp"
#include <cstdio>

Tile::Tile(const std::array<sf::Texture *, 5> &textures,
           const sf::Vector2f &scale)
    : textures(textures) {
  this->s_tile.setTexture(*this->textures[TextureId::UNCLICKED]);
  this->s_bomb.setTexture(*this->textures[TextureId::BOMB]);
  this->s_flag.setTexture(*this->textures[TextureId::FLAG]);

  this->s_tile.setScale(scale);
  this->s_bomb.setScale(scale);
  this->s_flag.setScale(scale);

  sf::Vector2f new_origin = {this->s_bomb.getGlobalBounds().width / 2,
                             this->s_bomb.getGlobalBounds().height / 2};
  this->s_bomb.setOrigin(new_origin);

  new_origin = {this->s_flag.getGlobalBounds().width / 2,
                this->s_flag.getGlobalBounds().height / 2};
  this->s_flag.setOrigin(new_origin);
}

void Tile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
  target.draw(this->s_tile);
  if (this->bomb && this->clicked) {
    target.draw(this->s_bomb);
  } else if (this->flagged) {
    target.draw(this->s_flag);
  }
}

void Tile::set_bomb() { this->bomb = true; }

bool Tile::is_bomb() const { return this->bomb; }

void Tile::click() {
  if (this->flagged) {
    return;
  }
  if (this->bomb) {
    this->s_tile.setTexture(*this->textures[TextureId::EXPLODED]);
  } else {
    this->s_tile.setTexture(*this->textures[TextureId::CLICKED]);
  }
  this->clicked = true;
}

void Tile::flag(bool mode) { this->flagged = mode; }

bool Tile::is_flagged() const { return this->flagged; }

bool Tile::is_clicked() const { return this->clicked; }

void Tile::set_position(const sf::Vector2f &position) {
  this->s_tile.setPosition(position);
  this->s_bomb.setPosition(
      position.x + this->s_bomb.getGlobalBounds().width / 2,
      position.y + this->s_bomb.getGlobalBounds().height / 2);
  this->s_flag.setPosition(
      position.x + this->s_flag.getGlobalBounds().width / 2,
      position.y + this->s_flag.getGlobalBounds().height / 2);
}

bool Tile::contains(const sf::Vector2f &position) const {
  return this->s_tile.getGlobalBounds().contains(position);
}