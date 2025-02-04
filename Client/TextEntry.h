#ifndef TEXTENTRY_H
#define TEXTENTRY_H

#include <SFML/Graphics.hpp>
#include <string>

class TextEntry {
private:
    sf::Text text;
    std::string userInput;

public:
    TextEntry(const sf::Font& font, unsigned int size, sf::Vector2f position);

    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& window) const;
};

#endif

