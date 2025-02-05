// Client.cpp
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>
#include <cstring>
#include <SFML/Graphics.hpp>
#include "Button.h"
#include "TextBox.h"
#include "TextMessage.h"

#pragma comment(lib, "ws2_32.lib") // Lier la bibliothèque Winsock

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

    // Envoi d'un message au serveur
    const char* message = "Hello from SFML client!";
    if (send(sock, message, static_cast<int>(strlen(message)), 0) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de l'envoi du message : " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Lancement d'un thread pour écouter les messages du serveur
    std::thread networkThread(networkListener, sock);

    sf::RenderWindow window(sf::VideoMode({ 800, 600 }), "Client SFML - Communication Réseau");

    // Chargement d'une police pour afficher un texte
    sf::Font font;
    if (!font.openFromFile("resources/font/Roboto.ttf")) {
        std::cerr << "Erreur de chargement de la police." << std::endl;
    }


    //UI
    TextMessage title("Multijoueur Pong", sf::Color::White, { 100, 20 }, font);
    TextMessage textIp("Adresse IP", sf::Color::White, { 100, 60 }, font);
    TextMessage textconfirmedIp("", sf::Color::White, { 100, 500 }, font);
    TextMessage textconfirmedpseudo("", sf::Color::White, { 100, 540 }, font);
    TextBox boxIp({ 100, 100 }, { 400, 60 }, font, textconfirmedIp, "Saisissez Adresse IP...", TextBox::CharType::IPAddress);
    TextMessage textpseudo("Pseudo", sf::Color::White, { 100, 160 }, font);
    TextBox boxpseudo({ 100, 200 }, { 400, 60 }, font, textconfirmedpseudo, "Saisissez un pseudo...", TextBox::CharType::Letter);
    Button buttoncreate("Creer partie", { 100, 280 }, { 180, 60 }, font);
    Button buttonjoin("Joindre partie", { 100, 360 }, { 180, 60 }, font);
    TextMessage texterror("Message erreur:", sf::Color::Red, { 100, 440 }, font);

    // Définition du callback
    /*myButton.setCallback([]()
        {
        std::cout << "Button clicked!" << std::endl;
        });*/

        // Boucle principale de la fenêtre SFML
    while (window.isOpen() && running) {

        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>()) {
                window.close();
                running = false;
            }

            sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

            //Inputs
            boxIp.handleEvent(*event, mousePos);
            boxpseudo.handleEvent(*event, mousePos);
            buttoncreate.update(mousePos, *event);
            buttonjoin.update(mousePos, *event);
        }

        //Update
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        boxIp.updateState(mousePos);
        boxpseudo.updateState(mousePos);

        window.clear(sf::Color::Black);

        //Draw
        title.Draw(window);
        textIp.Draw(window);
        boxIp.draw(window);
        textpseudo.Draw(window);
        boxpseudo.draw(window);
        textconfirmedIp.Draw(window);
        textconfirmedpseudo.Draw(window);
        buttoncreate.draw(window);
        buttonjoin.draw(window);
        texterror.Draw(window);

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
