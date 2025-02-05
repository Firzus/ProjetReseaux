#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>

class TextBox {
public:
    enum class State { Normal, Hovered, Focused };

    TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font& font, const std::string& initialText = "");

    void handleEvent(const sf::Event& event, const sf::Vector2f& mousePos);
    void draw(sf::RenderWindow& window);
    void updateState(const sf::Vector2f& mousePos);
    bool hasFocused = false;
    std::string getText() const;
    void updateColor();
    void setCallback(std::function<void()> callback) { m_callback = callback; }
    std::function<void()> m_callback;
private:
    sf::RectangleShape m_box;
    std::string m_stringtext;
    std::string m_stockedtext;
    sf::Text m_text;
    State m_state = State::Normal;
    
    
};

#endif
