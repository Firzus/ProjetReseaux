#ifndef BUTTON_H
#define BUTTON_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

class Button {
public:
    enum class State { Normal, Hovered, Pressed };

    Button(const std::string& text, sf::Vector2f position, sf::Vector2f size, sf::Font& font);

    void draw(sf::RenderWindow& window);
    void update(const sf::Vector2f& mousePos, const sf::Event& event);
    bool isHovered(const sf::Vector2f& mousePos) const;
    bool isClicked(const sf::Vector2f& mousePos, const sf::Event& event) const;
    void setCallback(std::function<void()> callback) { m_callback = callback; }

private:
    sf::RectangleShape m_shape;
    sf::Text m_label;
    State m_state = State::Normal;
    std::function<void()> m_callback;

    void updateColor(); // Met à jour la couleur du bouton
};

#endif
