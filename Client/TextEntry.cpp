#include "TextEntry.h"

TextEntry::TextEntry(const sf::Font& font, unsigned int size, sf::Vector2f position) {
    text.setFont(font);
    text.setCharacterSize(size);
    text.setFillColor(sf::Color::White);
    text.setPosition(position);
}

void TextEntry::handleEvent(const sf::Event& event) {
    if (event. == sf::Event::TextEntered) {
        if (event.text.unicode == '\b' && !userInput.empty()) { // Suppression
            userInput.pop_back();
        }
        else if (event.text.unicode < 128 && event.text.unicode != '\b') { // Ajout de caractères
            userInput += static_cast<char>(event.text.unicode);
        }
        text.setString(userInput);
    }
}

void TextEntry::draw(sf::RenderWindow& window) const {
    window.draw(text);
}
