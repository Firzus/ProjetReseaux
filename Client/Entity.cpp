#include "Entity.h"

Entity::Entity(float posX, float posY, float width, float height, sf::Color color)
{
    m_shape.setPosition({ posX, posY });
    m_shape.setSize({ width, height });
    m_shape.setFillColor(color);

}

void Entity::SetPosition(float posX, float posY)
{
    m_shape.setPosition({ posX, posY });
    
}

sf::Vector2f Entity::GetPosition()
{
    return m_shape.getPosition();
}

sf::Vector2f Entity::GetSize()
{
    return m_shape.getSize();
}

sf::RectangleShape Entity::GetShape()
{
    return m_shape;
}

void Entity::SetString(const std::string& textstring)
{
    //m_text.setString(textstring);
}

void Entity::Draw(sf::RenderWindow& window)
{
    window.draw(m_shape);
    onDraw(window);
    //window.draw(m_text);
}

void Entity::onDraw(sf::RenderWindow& window)
{
}

void Entity::onInitialize()
{
}

void Entity::Initialize()
{
    onInitialize();
}

void Entity::Update()
{

}
