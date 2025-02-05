#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <cstring>
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

	void CheckBtn();
	void UpdateBall();

	sf::RenderWindow& GetWindow();
	Input& GetInput();

private :
	sf::RenderWindow window;
	Input input;
	sf::Font font;

	sf::Text text_ScoreJ1;
	sf::Text text_ScoreJ2;

	sf::CircleShape circleShape;
	sf::RectangleShape rectangleshape_J1;
	sf::RectangleShape rectangleshape_J2;
	sf::RectangleShape rectangleshape_TraitMillieu;

	// Pos raquettes Left
	float posRaquettesLeftX;
	float posRaquettesLeftY;

	// Pos raquettes Right
	float posRaquettesRightX;
	float posRaquettesRightY;

	// Raquettes parameters
	float raquettespeed;
	float raquettesHeight;
	float raquettesWidth;

	// Info Balle
	float ballRadius;
	float ballSpeed;
	sf::Vector2f ballDir;
	float ballPosX;
	float ballPosY = WIN_HEIGHT / 2;

	// Score
	int scoreJ1;
	int scoreJ2;

};

#endif