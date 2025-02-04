#include "TextEntry.h"

TextEntry::TextEntry(const sf::Font& font, unsigned int size, sf::Vector2f position, bool sel) : textbox(font) 
{
    IsSelected = sel;
    box.setPosition(position);
    box.setSize({ 300, 50 });
    box.setFillColor(sf::Color::Blue);
       
    textbox.setFont(font);
    textbox.setCharacterSize(size);
    textbox.setFillColor(sf::Color::White);
    textbox.setPosition(position);

    if (IsSelected)
    {
        textbox.setString("_");
    }
    else
    {
        textbox.setString("");
    }
    
}

void TextEntry::handleEvent(const sf::Event& event) {
    

}

void TextEntry::draw(sf::RenderWindow& window) const 
{
    window.draw(box);
    window.draw(textbox);
}

void TextEntry::inputLogic(int charTyped)
{
    if (charTyped != DELETE_KEY && charTyped != ENTER_KEY && charTyped != ESCAPE_KEY)
    {
        text << static_cast<char>(charTyped);

    }
    else if (charTyped == DELETE_KEY)
    {
        if (text.str().length() > 0)
        {
            deletelastchar();
        }
    }
    textbox.setString(text.str() + " ");
}

void TextEntry::deletelastchar()
{
    std::string t = text.str();
    std::string newT = " ";
    for (int i = 0; i < t.length() - 1; i++)
    {
        newT += t[i];
    }
    text.str("");
    text << newT;

    textbox.setString(text.str());
}

void TextEntry::setlimit(bool Tof, int lim)
{
    hasLimit = Tof;
    limit = lim;
}

void TextEntry::setselected(bool isselected)
{
    IsSelected = isselected;
    if (!IsSelected)
    {
        std::string t = text.str();
        std::string newT = " ";
        for (int i = 0; i < t.length() - 1; i++)
        {
            newT += t[i];
        }
        textbox.setString(newT);
    }
}

void TextEntry::TypedOn(sf::Event input)
{
    if (IsSelected)
    {
        if (const auto* textEntered = input.getIf<sf::Event::TextEntered>())
        {
            if (textEntered->unicode < 128)
            {
                if (hasLimit)
                {
                    if (text.str().length() <= limit)
                    {
                        inputLogic(textEntered->unicode);
                    }
                    else if (text.str().length() > limit && textEntered->unicode == DELETE_KEY)
                    {
                        deletelastchar();
                    }
                }
                else
                {
                    inputLogic(textEntered->unicode);

                }
            }
                
        }
    }
}
