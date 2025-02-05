#include "Button.h"

Button::Button(const std::string& text, sf::Vector2f position, sf::Vector2f size, sf::Font& font) : m_label(font)
{
    m_shape.setSize(size);
    m_shape.setPosition(position);
    m_shape.setFillColor(sf::Color::Blue); // Couleur par défaut

    m_label.setFont(font);
    m_label.setString(text);
    m_label.setCharacterSize(20);
    m_label.setFillColor(sf::Color::White);
    m_label.setPosition({ position.x + 10, position.y + 10 });
}

void Button::update(const sf::Vector2f& mousePos, const sf::Event& event)
{
    if (isHovered(mousePos)) {
        m_state = State::Hovered;
        if (event.is<sf::Event::MouseButtonPressed>() && event.is<sf::Event::MouseLeft>()) {
            m_state = State::Pressed;
            if (m_callback) {
                m_callback();
            }
        }
    }
    else {
        m_state = State::Normal;
    }

    updateColor(); // Change la couleur selon l'état
}

void Button::updateColor()
{
    switch (m_state) {
    case State::Normal:
        m_shape.setFillColor(sf::Color::Blue); // Couleur normale
        break;
    case State::Hovered:
        m_shape.setFillColor(sf::Color::Green); // Couleur au survol
        break;
    case State::Pressed:
        m_shape.setFillColor(sf::Color::Red); // Couleur en cliquant
        break;
    }
}

bool Button::isHovered(const sf::Vector2f& mousePos) const
{
    return m_shape.getGlobalBounds().contains(mousePos);
}

bool Button::isClicked(const sf::Vector2f& mousePos, const sf::Event& event) const
{
    return isHovered(mousePos) && event.is<sf::Event::MouseButtonPressed>() && event.is<sf::Event::MouseLeft>();
}

void Button::draw(sf::RenderWindow& window)
{
    window.draw(m_shape);
    window.draw(m_label);
}
