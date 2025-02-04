#include "input.h"

// Constructeur
Input::Input()
{
    m_button.left = m_button.right = m_button.up = m_button.down = m_button.escape = false;
}

// Fonction qui accède à button (struct)
Input::Button Input::GetButton(void) const
{
    return m_button;
}

// Fonction de gestion des inputs
void Input::InputHandler(const sf::Event& event, sf::RenderWindow& window)
{
    if (event.is<sf::Event::Closed>())
    {
        window.close();
    }

    m_button.left = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left);
    m_button.right = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right);
    m_button.up = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up);
    m_button.down = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down);
    m_button.escape = sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape);

 }

