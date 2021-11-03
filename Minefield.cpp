#include "Minefield.hpp"
#include <stdexcept>


Minefield::Minefield(const sf::Vector2u &windowSize) {
    if(this->txt_tile_unclicked.loadFromFile("assets/tile_unclicked.png") == false) {
        throw std::runtime_error("Couldn't load tile texture");
    }
    if(this->txt_tile_clicked.loadFromFile("assets/tile_clicked.png") == false) {
        throw std::runtime_error("Couldn't load tile texture");
    }
    this->scaled_size = windowSize / Minefield::SQUARE_SIZE;
    this->scale = sf::Vector2f((double)this->scaled_size.x / (double)this->txt_tile_clicked.getSize().x,
        (double)this->scaled_size.y / (double)this->txt_tile_clicked.getSize().y);

    this->tile_clicked.setTexture(this->txt_tile_clicked);
    this->tile_unclicked.setTexture(this->txt_tile_unclicked);

    this->tile_clicked.setScale(this->scale);
    this->tile_unclicked.setScale(this->scale);

    sf::Vector2f position(0,0);
    for(unsigned int y=0; y<Minefield::SQUARE_SIZE; y++) {
        for(unsigned int x=0; x<Minefield::SQUARE_SIZE; x++) {
            this->tiles[y][x] = this->tile_unclicked;
            this->tiles[y][x].setPosition(position);
            position.x += this->scaled_size.x;
        }
        position.y += this->scaled_size.y;
        position.x = 0;
    }
}

void Minefield::update(sf::Vector2u clickPosition) {
    sf::Sprite *tile = this->find_tile_by_position(clickPosition);
    if(tile == nullptr) {
        return;
    }
    tile->setTexture(this->txt_tile_clicked);
}

sf::Sprite* Minefield::find_tile_by_position(sf::Vector2u clickPosition) {
    sf::Vector2f f_clickPosition(clickPosition.x, clickPosition.y);
    for(unsigned int y=0; y<Minefield::SQUARE_SIZE; y++) {
        for(unsigned int x=0; x<Minefield::SQUARE_SIZE; x++) {
            sf::Sprite& tile = this->tiles[y][x];
            if(tile.getGlobalBounds().contains(f_clickPosition) == true) {
                return &tile;
            }
        }
    }
    return nullptr;
}

void Minefield::draw(sf::RenderTarget& target, sf::RenderStates states) const {
    for(unsigned int y=0; y<Minefield::SQUARE_SIZE; y++) {
        for(unsigned int x=0; x<Minefield::SQUARE_SIZE; x++) {
            target.draw(this->tiles[y][x], states);
        }
    }
}