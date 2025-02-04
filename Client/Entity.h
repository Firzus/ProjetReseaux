#pragma once

#include <cstring>
#include <SFML/Graphics.hpp>

class Entity
{
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

