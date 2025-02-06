#include "Entity.h"

<<<<<<< HEAD
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
=======
Entity::Entity() : IsOffsetLock(false)
{
}

Entity::~Entity()
{
>>>>>>> main
}

void Entity::Draw(sf::RenderWindow& window)
{
<<<<<<< HEAD
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

=======
    // fonction en " virtual " 
}

void Entity::Update(float WindowHeight, float WindowWidth)
{
    // fonction en " virtual "
}

void Entity::Initialize(float WindowHeight, float WindowWidth)
{
    // fonction en " virtual "
}

void Entity::CheckCollision(sf::Vector2f velocity, float WindowHeight, float WindowWith)
{
    // fonction en " virtual "
}

// Ajoute un offset la position de l'entité
void Entity::AddEntityOffest(sf::Vector2f Offset)
{
    m_velocity = Offset;
    if (IsOffsetLock) {return;}
    m_EntityLocation += Offset;
}

// Deffinit la position de l'entité
void Entity::SetEntityLocation(sf::Vector2f newLocation)
{
    m_EntityLocation = newLocation;
}

void Entity::BlockOffset(bool Lock)
{
    IsOffsetLock = Lock;
}

// retourn la position de l'entié
sf::Vector2f Entity::GetEntityLocation()
{
    return m_EntityLocation;
}

sf::Vector2f Entity::GetVelocity()
{
    return m_velocity;
>>>>>>> main
}
