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

// Variable Game
Game game;

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

        // Initialize les élément a afficher
        game.Initialize();

        // Boucle principale de la fenêtre SFML
        while (game.GetWindow().isOpen() && running) {

            while (const std::optional<sf::Event> event = game.GetWindow().pollEvent())
            {
                if (event->is<sf::Event::Closed>()) {
                    game.GetWindow().close();
                    running = false;
                }

                game.SetInputHandle(*event, game.GetWindow());
            }

            game.Update(running);

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
