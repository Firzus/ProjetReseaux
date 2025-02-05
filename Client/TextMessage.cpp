#include "TextMessage.h"

TextMessage::TextMessage(const std::string& text, sf::Color color, sf::Vector2f position, sf::Font& font) : m_text(font)
{
    m_text.setString(text);
    m_text.setCharacterSize(24);
    m_text.setFillColor(color);
    m_text.setPosition(position);
}

void TextMessage::Draw(sf::RenderWindow& window)
{
    window.draw(m_text);
}

void TextMessage::Update()
{

}
