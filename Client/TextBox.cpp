#include "TextBox.h"

TextBox::TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font& font, const std::string& initialText) : m_text(font)
{
    m_box.setSize(size);
    m_box.setPosition(position);
    m_box.setFillColor(sf::Color::White);
    m_box.setOutlineThickness(2);

    m_text.setFont(font);
    m_text.setString(initialText);
    m_text.setCharacterSize(20);
    m_text.setFillColor(sf::Color::Black);
    m_text.setPosition(position);

    updateColor(); // Appliquer la couleur de base
}

void TextBox::handleEvent(const sf::Event& event, const sf::Vector2f& mousePos)
{
    if (event.is<sf::Event::MouseButtonPressed>()) {
        if (m_box.getGlobalBounds().contains(mousePos)) {
            m_state = State::Focused;
        }
        else {
            m_state = State::Normal;
        }
        updateColor();
    }

    if (m_state == State::Focused && event.is<sf::Event::TextEntered>()) {
        
        char enteredChar = static_cast<char>(event.is<sf::Event::TextEntered>());
        std::string str = m_text.getString();

        if (enteredChar == 8) { // Backspace
            if (!str.empty()) {
                str.pop_back();
                m_text.setString(str);
            }
        }
        else if (enteredChar >= 32 && enteredChar <= 126) { // Lettres, chiffres et symboles
            str += enteredChar;
            m_text.setString(str);
        }
    }
}

void TextBox::updateState(const sf::Vector2f& mousePos)
{
    if (m_state != State::Focused) { // On ne change pas l'état si déjà en focus
        m_state = m_box.getGlobalBounds().contains(mousePos) ? State::Hovered : State::Normal;
        updateColor();
    }
}

void TextBox::updateColor()
{
    switch (m_state) {
    case State::Normal:
        m_box.setOutlineColor(sf::Color::Black);
        break;
    case State::Hovered:
        m_box.setOutlineColor(sf::Color::Green);
        break;
    case State::Focused:
        m_box.setOutlineColor(sf::Color::Blue);
        break;
    }
}

void TextBox::draw(sf::RenderWindow& window)
{
    window.draw(m_box);
    window.draw(m_text);
}

std::string TextBox::getText() const
{
    return m_text.getString();
}
