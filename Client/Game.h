#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstring>
#include "GameManager.h"
#include "input.h"
#include <SFML/Graphics.hpp>

// Constante
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

class Game
{

public :
	Game();
	~Game();

	void Initialize();
	void Update(bool running);
	void SetInputHandle(const sf::Event& event, sf::RenderWindow& window);

	sf::RenderWindow& GetWindow();
	Input& GetInput();

private :

	sf::RenderWindow window;
	Input input;
	sf::Font font;

	sf::Text text_ScoreJ1;
	sf::Text text_ScoreJ2;

	GameManager m_GameManager;

};

#endif