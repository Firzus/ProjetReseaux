#include "Text.h"

Text::Text(const sf::Font& font, unsigned int size, sf::Vector2f position) : text(font)
{
    box.setPosition(position);
    box.setSize({ 300, 50 });
    box.setFillColor(sf::Color::Red);

    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
    text.setPosition(position);

    text.setString("État actuel: ");
}

void Text::draw(sf::RenderWindow& window) const
{
    window.draw(box);
	window.draw(text);
}
