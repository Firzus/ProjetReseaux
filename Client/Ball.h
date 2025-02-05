#ifndef BALL_H
#define BALL_H

#include "Entity.h"
#include "Raquette.h"
#include <vector>
#include "SFML/Graphics.hpp"

class Ball : public Entity
{
public : 

	Ball();
	~Ball();

	void Update(float WindowHeight, float WindowWidth) override;
	void Draw(sf::RenderWindow& window) override;
	void Initialize(float WindowHeight, float WindowWidth) override;
	void CheckCollision(sf::Vector2f velocity, float WindowHeight = 0, float WindowWidth = 0) override;

	void CheckCollisionRaquette(std::vector<Raquette*> Raquettes);

private :

	sf::CircleShape m_BallShape;
	sf::Vector2f m_ballDir;

	

	float m_ballRadius;
	float m_ballSpeed;
	float m_ballPosX;
	float m_ballPosY;

	bool m_SimulatePhysic;
};

#endif