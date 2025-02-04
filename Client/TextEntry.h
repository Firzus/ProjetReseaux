#ifndef TEXTENTRY_H
#define TEXTENTRY_H

#include <SFML/Graphics.hpp>
#include <string>
#include <sstream>

#define DELETE_KEY 8
#define ENTER_KEY 13
#define ESCAPE_KEY 27

class TextEntry 
{
private:
    sf::RectangleShape box;
    sf::Text textbox;
    std::ostringstream text;
    std::string userInput;
    bool IsSelected;
    bool hasLimit;
    int limit;

public:
    TextEntry(const sf::Font& font, unsigned int size, sf::Vector2f position, bool sel);

    void handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& window) const;

    void inputLogic(int charTyped);
    void deletelastchar();

    void setlimit(bool Tof, int lim);
    void setselected(bool isselected);

    void TypedOn(sf::Event input);

    std::string getString() { return text.str(); }

    
};

#endif

