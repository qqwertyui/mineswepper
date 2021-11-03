#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <cstdio>

#include "Minefield.hpp"

int main() {
    sf::RenderWindow window(sf::VideoMode(480, 480), "Mineswepper", 
    sf::Style::Close);
    Minefield map(window.getSize());

    while(window.isOpen()) {
        sf::Event event;
        while(window.pollEvent(event)) {
            if(event.type == sf::Event::Closed) {
                window.close();
            } else if(event.type == sf::Event::KeyPressed) {
                if(event.key.code == sf::Keyboard::Key::Escape) {
                    window.close();
                }
            } else if(event.type == sf::Event::MouseButtonPressed) {
                map.update(sf::Vector2u(event.mouseButton.x, event.mouseButton.y));
            }
        }
        window.clear(sf::Color::White);
        window.draw(map);
        window.display();
    }

    return 0;
}