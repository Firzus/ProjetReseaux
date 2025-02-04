#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Text
{

public:

    Text(const sf::Font& font, unsigned int size, sf::Vector2f position);

    void draw(sf::RenderWindow& window) const;

private:

    sf::RectangleShape box;
    sf::Text text;
    std::string userInput;

};

