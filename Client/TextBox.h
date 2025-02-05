#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <iostream>

class TextBox {
public:
    enum class State { Normal, Hovered, Focused };

    TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font& font, const std::string& initialText = "");

    void handleEvent(const sf::Event& event, const sf::Vector2f& mousePos);
    void draw(sf::RenderWindow& window);
    void updateState(const sf::Vector2f& mousePos);

    std::string getText() const; // Nouvelle fonction pour récupérer le texte
    void updateColor();
private:
    sf::RectangleShape m_box;
    sf::Text m_text;
    State m_state = State::Normal;

    
};

#endif
