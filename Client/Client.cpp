// Client.cpp
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>
#include <SFML/Graphics.hpp>
#include <sstream>
#include <chrono>

#pragma comment(lib, "ws2_32.lib")

// Variable globale pour contrôler la boucle d'exécution
bool running = true;
sf::Vector2f currentPosition(400.f, 300.f); // Position actuelle de la balle
sf::Vector2f targetPosition = currentPosition;
float interpolationSpeed = 0.1f;

sf::Vector2f lerp(const sf::Vector2f& start, const sf::Vector2f& end, float t) {
    return start + t * (end - start);
}

// Fonction exécutée dans un thread dédié pour recevoir les messages du serveur
void networkListener(SOCKET sock) {
    const int bufferSize = 4096;
    char buffer[bufferSize];

    while (running) {
        ZeroMemory(buffer, bufferSize);
        int bytesReceived = recv(sock, buffer, bufferSize, 0);
        if (bytesReceived > 0) {
            std::istringstream dataStream(buffer);
            float x, y;
            char comma;
            if (dataStream >> x >> comma >> y) {
                targetPosition = sf::Vector2f(x, y); // Nouvelle position cible
                std::cout << "Nouvelle position reçue : (" << x << ", " << y << ")\n";
            }
        }
        else {
            running = false;
            break;
        }
    }
}

int main() {
    // Initialisation de Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Erreur WSAStartup" << std::endl;
        return 1;
    }

    // Création du socket TCP/IP
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Erreur de création du socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Configuration de l'adresse du serveur
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(3000);  // Port 3000
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        std::cerr << "Adresse IP invalide" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Connexion au serveur
    if (connect(sock, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Erreur de connexion : " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    std::cout << "Connecté au serveur." << std::endl;

    // Lancement d'un thread pour écouter les messages du serveur
    std::thread networkThread(networkListener, sock);

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Client SFML - Communication Réseau");

    // Chargement d'une police pour afficher un texte
    sf::Font font;
    if (!font.openFromFile("resources/font/Roboto.ttf")) {
        std::cerr << "Erreur de chargement de la police." << std::endl;
    }

    // Configuration du texte à afficher
    sf::Text text(font);
    text.setString("Client SFML : Connecté au serveur sur le port 3000");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);
    text.setPosition({ 50.f, 50.f });

    // Ball test
    sf::CircleShape ball(10.f);
    ball.setFillColor(sf::Color::Red);
    ball.setPosition(currentPosition);

    auto lastTime = std::chrono::high_resolution_clock::now();

    // Boucle principale de la fenêtre SFML
    while (window.isOpen() && running) {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                running = false;
            }
        }

        // Interpolation de la position
        currentPosition = lerp(currentPosition, targetPosition, interpolationSpeed);

        // Mise à jour de l'affichage
        ball.setPosition(currentPosition);

        window.clear(sf::Color::Black);
        window.draw(ball);
        window.draw(text);
        window.display();
    }

    // Arrêt de l'écoute réseau
    running = false;
    if (networkThread.joinable())
        networkThread.join();

    // Fermeture du socket et nettoyage de Winsock
    closesocket(sock);
    WSACleanup();

    return 0;
}
