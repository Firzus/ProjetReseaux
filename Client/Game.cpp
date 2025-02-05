#include "Game.h"

Game::Game() :
    scoreJ1(0),
    scoreJ2(0),
    window(sf::VideoMode({ WIN_WIDTH, WIN_HEIGHT }), "Client SFML - Communication Réseau"),
    text_ScoreJ1(font),
    text_ScoreJ2(font)
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
    text_ScoreJ1.setPosition({ (WIN_WIDTH / 2.0f) - 50 - 35, 10 });
    // Score J2
    text_ScoreJ2.setFont(font);
    text_ScoreJ2.setString(std::to_string(scoreJ2));
    text_ScoreJ2.setCharacterSize(50);
    text_ScoreJ2.setFillColor(sf::Color::White);
    text_ScoreJ2.setPosition({ (WIN_WIDTH / 2.0f) + 35, 10 });



    m_GameManager.AddEntity(new Raquette);
    m_GameManager.AddEntity(new Raquette);
    m_GameManager.AddEntity(new Ball);

    m_GameManager.Initialise(WIN_HEIGHT,WIN_WIDTH);

}

void Game::Update(bool running)
{
        m_GameManager.Update(WIN_HEIGHT,WIN_WIDTH);

        // Texte du score
        text_ScoreJ1.setString(std::to_string(scoreJ1));
        text_ScoreJ2.setString(std::to_string(scoreJ2));

        window.clear(sf::Color::Black);

        m_GameManager.Draw(window);

        window.draw(text_ScoreJ1);
        window.draw(text_ScoreJ2);
        window.display();
}

void Game::SetInputHandle(const sf::Event& event, sf::RenderWindow& window)
{
    input.InputHandler(event, window);
    m_GameManager.SetInput(input);
}

/*void Game::UpdateBall()
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
*/

sf::RenderWindow& Game::GetWindow()
{
    return window;
}

Input& Game::GetInput()
{
    return input;
}

