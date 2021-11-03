#ifndef MINEFIELD_HPP
#define MINEFIELD_HPP

#include <SFML/Graphics.hpp>
#include <string_view>
#include <vector>

class Minefield : public sf::Drawable {
public:
    Minefield(const sf::Vector2u &windowSize);
    Minefield() = delete;
    ~Minefield() = default;

    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    void update(sf::Vector2u clickPosition);

    static constexpr unsigned int SQUARE_SIZE = 20;
private:
    sf::Vector2u scaled_size;
    sf::Vector2f scale;

    sf::Sprite tiles[Minefield::SQUARE_SIZE][Minefield::SQUARE_SIZE];
    sf::Texture txt_tile_clicked, txt_tile_unclicked;
    sf::Sprite tile_clicked, tile_unclicked;

    sf::Sprite* find_tile_by_position(sf::Vector2u clickPosition);
};

#endif