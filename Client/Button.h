#pragma once
#include "Entity.h"
class Button : public Entity
{
private:
    sf::Color m_hoverColor;
    sf::Color m_clickColor;
    sf::Color m_normalColor;

    bool m_isClicked = false;

public:
    Button(float posX, float posY, float width, float height, sf::Color color, sf::Color hoverColor = sf::Color::Green, sf::Color clickColor = sf::Color::Red)
        : Entity(posX, posY, width, height, color), m_normalColor(color), m_hoverColor(hoverColor), m_clickColor(clickColor) { }

    void onUpdate(sf::RenderWindow& window);

    bool IsClicked(sf::Vector2f cursorPos); // Vérifie si le bouton est cliqué
};

