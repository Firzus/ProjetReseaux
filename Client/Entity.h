<<<<<<< HEAD
#pragma once

#include <cstring>
=======
#ifndef ENTITY_H
#define ENTITY_H

>>>>>>> main
#include <SFML/Graphics.hpp>

class Entity
{
<<<<<<< HEAD
protected:
	sf::RectangleShape m_shape;
	sf::Color m_color;
	float m_speed = 1.0f;

public:
	Entity(float posX, float posY, float width, float height, sf::Color color);
	~Entity() = default;

	void SetPosition(float posX, float posY);
	sf::Vector2f GetPosition();
	void SetSpeed(float speed) { m_speed = speed;  }
	void SetSize(float width, float height) {m_shape.setSize({width, height});}
	sf::Vector2f GetSize();
	sf::RectangleShape GetShape();
	void SetString(const std:: string& textstring);
	void Draw(sf::RenderWindow& window);
	virtual void onDraw(sf::RenderWindow& window);
	virtual void onInitialize();
	
private:
	void Initialize();
	void Update();
};

=======
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
>>>>>>> main
