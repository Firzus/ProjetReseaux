#include "Button.h"

// Vérifie si le bouton est cliqué
bool Button::IsClicked(sf::Vector2f cursorPos)
{
    sf::FloatRect bounds = m_shape.getGlobalBounds();
    return bounds.contains(cursorPos);
}

void Button::onDraw(sf::RenderWindow& window)
{
    window.draw(m_text);
}

Button::Button(float posX, float posY, float width, float height, sf::Color color, sf::Color hoverColor, sf::Color clickColor, sf::Font font) : Entity(posX, posY, width, height, color), m_normalColor(color), m_hoverColor(hoverColor), m_clickColor(clickColor), m_text(font)
{
    m_text.setString("ButtonTest");
    m_text.setCharacterSize(24);
    m_text.setFillColor(sf::Color::Red);
    m_text.setPosition({posX, posY});
}

void Button::onUpdate(sf::RenderWindow& window)
{
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    sf::Vector2f cursorPos = window.mapPixelToCoords(mousePos);

    // Vérifie si la souris est au-dessus du bouton
    if (IsClicked(cursorPos))
    {
        m_shape.setFillColor(m_hoverColor);  // Couleur survolée

        if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && !m_isClicked)
        {
            m_isClicked = true;
            m_shape.setFillColor(m_clickColor); // Change la couleur au clic
            
        }
    }
    else
    {
        if (!m_isClicked)
            m_shape.setFillColor(m_normalColor); // Retour à la couleur normale
    }

    // Réinitialise l'état du bouton quand le clic est relâché
    if (!sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && m_isClicked)
    {
        m_isClicked = false;
        m_shape.setFillColor(m_hoverColor); // Retour à la couleur de survol
    }

}

