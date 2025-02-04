#include "Game.h"

Game::Game() :
    posRaquettesLeftX(50.0f),
    posRaquettesLeftY(WIN_HEIGHT / 2),
    posRaquettesRightX(WIN_WIDTH - 70),
    posRaquettesRightY(posRaquettesLeftY),
    raquettespeed(0.07f),
    raquettesHeight(150.0f),
    raquettesWidth(20.0f),
    ballRadius(15),
    ballSpeed(0.03),
    ballDir(sf::Vector2f(2.0f, 0.5f)),
    ballPosX(WIN_WIDTH / 2),
    ballPosY(WIN_HEIGHT / 2),
    scoreJ1(0),
    scoreJ2(0),
    window(sf::VideoMode({ WIN_WIDTH, WIN_HEIGHT }), "Client SFML - Communication Réseau"),
{}

Game::~Game()
{}

void Game::Initialize()
{
    // Chargement de la police avec gestion des erreurs
    if (!font.openFromFile("resources/font/Roboto.ttf")) {
        throw std::runtime_error("Erreur de chargement de la police.");
    }

    // Configuration du texte à afficher
    // Score J1
    text_ScoreJ1.setFont(font);
    text_ScoreJ1.setString(std::to_string(scoreJ1));
    text_ScoreJ1.setCharacterSize(50);
    text_ScoreJ1.setFillColor(sf::Color::White);
    text_ScoreJ1.setPosition({ (WIN_WIDTH / 2) - 50 - 35, 10 });
    // Score J2
    text_ScoreJ2.setFont(font);
    text_ScoreJ2.setString(std::to_string(scoreJ2));
    text_ScoreJ2.setCharacterSize(50);
    text_ScoreJ2.setFillColor(sf::Color::White);
    text_ScoreJ2.setPosition({ (WIN_WIDTH / 2) + 35, 10 });

    // Préparation des formes
    // Balle
    circleShape.setRadius(ballRadius);
    circleShape.setPosition(sf::Vector2f(ballPosX, ballPosY));

    // Raquette gauche
    rectangleshape_J1.setSize(sf::Vector2f(raquettesWidth, raquettesHeight));
    rectangleshape_J1.setPosition(sf::Vector2f(posRaquettesLeftX, posRaquettesLeftY));

    // Raquette droite
    rectangleshape_J2.setSize(sf::Vector2f(raquettesWidth, raquettesHeight));
    rectangleshape_J2.setPosition(sf::Vector2f(posRaquettesRightX, posRaquettesRightY));

    // Trait du millieu
    rectangleshape_TraitMillieu.setSize(sf::Vector2f(7, WIN_HEIGHT));
    rectangleshape_TraitMillieu.setPosition(sf::Vector2f((WIN_WIDTH / 2) - 7, 0));
}

void Game::Update(bool running)
{
    // Boucle principale de la fenêtre SFML
    while (window.isOpen() && running) {

        while (const std::optional<sf::Event> event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                running = false;
            }

            input.InputHandler(*event, window);
        }
        // Gestion clavier
        CheckBtn();

        // Gestion des shapes des raquettes, balle
        rectangleshape_J1.setPosition(sf::Vector2f(posRaquettesLeftX, posRaquettesLeftY));
        rectangleshape_J2.setPosition(sf::Vector2f(posRaquettesRightX, posRaquettesRightY));
        circleShape.setPosition(sf::Vector2f(ballPosX, ballPosY));

        // Gestion de la balle
        UpdateBall();

        // Texte du score
        text_ScoreJ1.setString(std::to_string(scoreJ1));
        text_ScoreJ2.setString(std::to_string(scoreJ2));

        window.clear(sf::Color::Black);
        window.draw(text_ScoreJ1);
        window.draw(text_ScoreJ2);
        window.draw(circleShape);
        window.draw(rectangleshape_J1);
        window.draw(rectangleshape_J2);
        window.draw(rectangleshape_TraitMillieu);
        window.display();
    }
}

void Game::CheckBtn()
{
    // Raquette gauche
    if (input.GetButton().Z)
    {
        posRaquettesLeftY -= raquettespeed;
        if (posRaquettesLeftY < 0)
            posRaquettesLeftY = 0;
    }
    if (input.GetButton().S)
    {
        posRaquettesLeftY += raquettespeed;
        if (posRaquettesLeftY + raquettesHeight > WIN_HEIGHT)
            posRaquettesLeftY = WIN_HEIGHT - raquettesHeight;
    }

    // Raquette droit
    if (input.GetButton().up)
    {
        posRaquettesRightY -= raquettespeed;
        if (posRaquettesRightY < 0)
            posRaquettesRightY = 0;
    }
    if (input.GetButton().down)
    {
        posRaquettesRightY += raquettespeed;
        if (posRaquettesRightY + raquettesHeight > WIN_HEIGHT)
            posRaquettesRightY = WIN_HEIGHT - raquettesHeight;
    }
}

void Game::UpdateBall()
{
    // Position de la balle
    ballPosX += ballDir.x * ballSpeed;
    ballPosY += ballDir.y * ballSpeed;
    // Collision balle
    // raquette gauche ou droite touchée ?
    if ((ballPosX - ballRadius < posRaquettesLeftX + raquettesWidth &&
        ballPosX + ballRadius > posRaquettesLeftX &&
        ballPosY - ballRadius < posRaquettesLeftY + raquettesHeight &&
        ballPosY + ballRadius > posRaquettesLeftY)
        ||
        (ballPosX + ballRadius > posRaquettesRightX - raquettesWidth &&
            ballPosX - ballRadius < posRaquettesRightX &&
            ballPosY - ballRadius < posRaquettesRightY + raquettesHeight &&
            ballPosY + ballRadius> posRaquettesRightY))
    {
        ballDir.x *= -1;
    }

    // hit mur gauche
    if (ballPosX < 0)
    {
        scoreJ2++;
        ballPosX = WIN_WIDTH / 2;
        ballPosY = WIN_HEIGHT / 2;
        ballDir.x = fabs(ballDir.x) * -1;
        ballDir.y *= -1;
    }
    // hit mur droit
    if (ballPosX + ballRadius > WIN_WIDTH)
    {
        scoreJ1++;
        ballPosX = WIN_WIDTH / 2;
        ballPosY = WIN_HEIGHT / 2;
        ballDir.x = fabs(ballDir.x);
        ballDir.y *= -1;
    }

    // mur haut ou bas
    if (ballPosY + ballRadius > WIN_HEIGHT || ballPosY - ballRadius < 0) {
        ballDir.y *= -1;
    }

}

