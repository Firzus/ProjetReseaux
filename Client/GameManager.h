#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include <vector>
#include "Entity.h"
#include "Raquette.h"
#include "Ball.h"
#include "input.h"

class GameManager
{
public : 

	GameManager();
	~GameManager();

	int GetScoreJ1();
	int GetScoreJ2();

	void Draw(sf::RenderWindow& window);
	void Initialise(float WindowHeight, float WindowWidth);
	void Update(float WindowHeight, float WindowWidth);
	void AddEntity(Entity* entity);
	void CheckBtn(float WindowHeight, float WindowWidth);
	void SetInput(Input& input);

	std::vector<Entity*> GetEntitties();


private :

	std::vector<Entity*> m_Entitties;
	std::vector<Raquette*> m_Raquettes;

	Input m_input;

	int m_PlayerIndex;

	int scoreJ1;
	int scoreJ2;

};

#endif