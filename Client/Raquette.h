#ifndef RAQUETTE_H
#define RAQUETTE_H

#include "Entity.h"
#include "SFML/Graphics.hpp"

class Raquette : public Entity
{
public : 

	Raquette();
	~Raquette();

	void Update(float WindowHeight, float WindowWidth) override;
	void Draw(sf::RenderWindow& window) override;
	void Initialize(float WindowHeight, float WindowWidth) override;
	void CheckCollision(sf::Vector2f velocity,float WindowHeight = 0, float WindowWith = 0) override;

	// Setter
	void SetPlayerIndex(int index);

	// Getter
	int GetPlayerIndex();
	float GetRaquetteSpeed();
	float GetRaquetteHeight();

private : 

	sf::RectangleShape m_RaquetteShape;

	float m_RaquetteSpeed;
	float m_RaquettesHeight;
	float m_RaquettesWidth;

	int m_PlayerIndex;

};

#endif