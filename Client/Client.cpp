#include "client.h"

// Variable globale pour contrôler la boucle d'exécution
bool running = true;

// Fonction exécutée dans un thread dédié pour recevoir les messages du serveur
void networkListener(SOCKET sock) {
    const int bufferSize = 4096;
    char buffer[bufferSize];

    while (running) {
        ZeroMemory(buffer, bufferSize);
        int bytesReceived = recv(sock, buffer, bufferSize, 0);
        if (bytesReceived > 0) {
            std::cout << "Message reçu du serveur : " << buffer << std::endl;
        }
        else if (bytesReceived == 0) {
            std::cout << "Connexion fermée par le serveur." << std::endl;
            running = false;
            break;
        }
        else {
            std::cerr << "Erreur de réception : " << WSAGetLastError() << std::endl;
            running = false;
            break;
        }
    }
}

sf::RenderWindow window;
Input input;
sf::Font font;

// Pos raquettes Left
float posRaquettesLeftX = 50.0f;
float posRaquettesLeftY = WIN_HEIGHT / 2;

// Pos raquettes Right
float posRaquettesRightX = WIN_WIDTH - 70;
float posRaquettesRightY = posRaquettesLeftY;

// Raquettes parameters
float raquettespeed = 0.07f;
float raquettesHeight = 150.0f;
float raquettesWidth = 20.0f;

// Info Balle
float ballSpeed = 0.03;
sf::Vector2f ballDir = sf::Vector2f(2.0f, 0.5f);
float ballPosX = WIN_WIDTH / 2;
float ballPosY = WIN_HEIGHT / 2;

// Score
int scoreJ1 = 0;
int scoreJ2 = 0;

void CheckBtn()
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

void UpdateBall()
{
    // Position de la balle
    ballPosX += ballDir.x * ballSpeed;
    ballPosY += ballDir.y * ballSpeed;
    // Collision balle
    // raquette gauche ou droite touchée ?
    if ((ballPosX < posRaquettesLeftX + raquettesWidth &&
        ballPosX > posRaquettesLeftX &&
        ballPosY < posRaquettesLeftY + raquettesHeight &&
        ballPosY > posRaquettesLeftY)
        ||
        (ballPosX > posRaquettesRightX - raquettesWidth &&
            ballPosX < posRaquettesRightX &&
            ballPosY < posRaquettesRightY + raquettesHeight &&
            ballPosY > posRaquettesRightY)) 
    {
        ballDir.x *= -1;
    }

    // hit mur gauche
    if (ballPosX < 0) 
    {
        scoreJ2++;
        ballPosX = WIN_WIDTH / 2;
        ballPosY = WIN_HEIGHT / 2;
        ballDir.x = fabs(ballDir.x)*-1;
        ballDir.y *= -1;
    }
    // hit mur droit
    if (ballPosX > WIN_WIDTH)
    {
        scoreJ1++;
        ballPosX = WIN_WIDTH / 2;
        ballPosY = WIN_HEIGHT / 2;
        ballDir.x = fabs(ballDir.x);
        ballDir.y *= -1;
    }

    // mur haut ou bas
    if (ballPosY > WIN_HEIGHT || ballPosY < 0) {
        ballDir.y *= -1;
    }

}


int main() {
    // Initialisation de Winsock
    WSADATA wsaData;
    try {
        if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
            throw std::runtime_error("Erreur WSAStartup");
        }

        // Création du socket TCP/IP
        SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if (sock == INVALID_SOCKET) {
            throw std::runtime_error("Erreur de création du socket : " + std::to_string(WSAGetLastError()));
        }

        // Configuration de l'adresse du serveur
        sockaddr_in serverAddr;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_port = htons(3000);  // Port 3000
        if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
            throw std::runtime_error("Adresse IP invalide");
        }

        // Connexion au serveur
        if (connect(sock, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
            throw std::runtime_error("Erreur de connexion : " + std::to_string(WSAGetLastError()));
        }

        std::cout << "Connecté au serveur." << std::endl;

        // Envoi d'un message au serveur
        const char* message = "Hello from SFML client!";
        if (send(sock, message, static_cast<int>(strlen(message)), 0) == SOCKET_ERROR) {
            throw std::runtime_error("Erreur lors de l'envoi du message : " + std::to_string(WSAGetLastError()));
        }

        // Lancement d'un thread pour écouter les messages du serveur
        std::thread networkThread(networkListener, sock);

        // Création de la fenêtre SFML et gestion des exceptions SFML
        sf::RenderWindow window(sf::VideoMode({ WIN_WIDTH, WIN_HEIGHT }), "Client SFML - Communication Réseau");

        // Chargement de la police avec gestion des erreurs
        if (!font.openFromFile("resources/font/Roboto.ttf")) {
            throw std::runtime_error("Erreur de chargement de la police.");
        }

        // Configuration du texte à afficher
        sf::Text text(font);
        text.setString(std::to_string(scoreJ1) + " | " + std::to_string(scoreJ2));
        text.setCharacterSize(24);
        text.setFillColor(sf::Color::White);
        text.setPosition({ WIN_WIDTH / 2, 10});

        // Préparation des formes
        // Balle
        sf::CircleShape circleShape(15);
        circleShape.setPosition(sf::Vector2f(ballPosX, ballPosY));

        // Raquette gauche
        sf::RectangleShape rectangleshape(sf::Vector2f(raquettesWidth, raquettesHeight));
        rectangleshape.setPosition(sf::Vector2f(posRaquettesLeftX, posRaquettesLeftY));

        // Raquette droite
        sf::RectangleShape rectangleshape2(sf::Vector2f(raquettesWidth, raquettesHeight));
        rectangleshape2.setPosition(sf::Vector2f(posRaquettesRightX, posRaquettesRightY));

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
            rectangleshape.setPosition(sf::Vector2f(posRaquettesLeftX, posRaquettesLeftY));
            rectangleshape2.setPosition(sf::Vector2f(posRaquettesRightX, posRaquettesRightY));
            circleShape.setPosition(sf::Vector2f(ballPosX, ballPosY));

            // Gestion de la balle
            UpdateBall();

            // Texte du score
            text.setString(std::to_string(scoreJ1) + " | " + std::to_string(scoreJ2));

            window.clear(sf::Color::Black);
            window.draw(text);
            window.draw(circleShape);
            window.draw(rectangleshape);
            window.draw(rectangleshape2);
            window.display();
        }

        // Arrêt de l'écoute réseau
        running = false;
        if (networkThread.joinable())
            networkThread.join();

        // Fermeture du socket et nettoyage de Winsock
        closesocket(sock);
        WSACleanup();

    }
    catch (const std::runtime_error& e) {
        std::cerr << "Exception standard: " << e.what() << std::endl;
        running = false;
        WSACleanup();
    }
    catch (const sf::Exception& e) {
        std::cerr << "Exception SFML: " << e.what() << std::endl;
        running = false;
        WSACleanup();
    }
    catch (...) {
        std::cerr << "Une erreur inconnue est survenue." << std::endl;
        running = false;
        WSACleanup();
    }

    return 0;
}
