#ifndef TEXTBOX_H
#define TEXTBOX_H

#include <SFML/Graphics.hpp>
#include <iostream>
#include <functional>
#include "TextMessage.h"

class TextBox {
public:
    enum class State { Normal = 0, Hovered = 1, Focused = 2 };
    enum class CharType { Number = 0, Letter = 1, IPAddress = 2 };  // Ajout de IPAddress

    TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font& font, TextMessage& textMessage,
        const std::string& initialText = "", CharType charType = CharType::Letter);

    void handleEvent(const sf::Event& event, const sf::Vector2f& mousePos);
    void draw(sf::RenderWindow& window);
    void updateState(const sf::Vector2f& mousePos);
    bool hasFocused = false;
    std::string getText() const;
    void updateColor();
    void setCallback(std::function<void()> callback) { m_callback = callback; }
    std::function<void()> m_callback;
    size_t maxChar = 20;

private:
    bool isValidChar(char enteredChar);  // Fonction de validation des caractères

    sf::RectangleShape m_box;
    std::string m_stringtext;
    std::string m_stockedtext;
    sf::Text m_text;
    State m_state = State::Normal;
    CharType m_charType;
    TextMessage& m_textMessage;  // Référence à TextMessage
};

#endif
