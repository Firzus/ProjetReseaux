#ifndef ENTITY_H
#define ENTITY_H

#include <SFML/Graphics.hpp>

class Entity
{
public :

	Entity();
	~Entity();

	virtual void Draw(sf::RenderWindow& window);
	virtual void Update(float WindowHeight, float WindowWidth);
	virtual void Initialize(float WindowHeight, float WindowWidth);
	virtual void CheckCollision(sf::Vector2f velocity, float WindowHeight = 0, float WindowWith = 0);

	void AddEntityOffest(sf::Vector2f Offset);



	//Setter
	void SetEntityLocation(sf::Vector2f newLocation);
	void BlockOffset(bool Lock);

	//Getter
	sf::Vector2f GetEntityLocation();
	sf::Vector2f GetVelocity();

private : 

	sf::Vector2f m_EntityLocation;
	sf::Vector2f m_velocity;

	bool IsOffsetLock;


};

#endif