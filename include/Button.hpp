#ifndef BUTTON_HPP
#define BUTTON_HPP

#include <SFML/Graphics.hpp>

class Button : public sf::Drawable {
public:
  typedef void (*buttonCallback)();

  Button(sf::Vector2f position, sf::Vector2f scale = {1.f, 1.f});
  virtual void draw(sf::RenderTarget &target,
                    sf::RenderStates states) const override;
  bool is_hover(const sf::Vector2f &position) const;
  void on_button_click(buttonCallback callback);
  void click();
  void release();

  sf::Vector2f get_size();
  void set_position(const sf::Vector2f &position);

private:
  buttonCallback m_callback;
  sf::Sprite m_button;
};

#endif