#include "Entity.h"

Entity::Entity() : IsOffsetLock(false)
{
}

Entity::~Entity()
{
}

void Entity::Draw(sf::RenderWindow& window)
{
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
}
