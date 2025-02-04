#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>
#include <vector>
#include <random>
#include <chrono>
#include <string>

#pragma comment(lib, "ws2_32.lib")

// Fonction qui gère la communication avec un client

void handleClient(SOCKET clientSocket) {
    std::mt19937 rng(std::random_device{}());
    std::uniform_real_distribution<float> distX(0.f, 800.f);
    std::uniform_real_distribution<float> distY(0.f, 600.f);

    while (true) {
        float x = distX(rng);
        float y = distY(rng);

        std::string positionMessage = std::to_string(x) + "," + std::to_string(y);
        send(clientSocket, positionMessage.c_str(), static_cast<int>(positionMessage.size()), 0);

        std::this_thread::sleep_for(std::chrono::seconds(2)); // Envoi toutes les 2 secondes
    }

    closesocket(clientSocket);
}

int main() {
    // Initialisation de Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Erreur WSAStartup" << std::endl;
        return 1;
    }

    // Création du socket d'écoute
    SOCKET listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listeningSocket == INVALID_SOCKET) {
        std::cerr << "Erreur création du socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Configuration de l'adresse du serveur
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(3000); // Port 3000

    // Liaison du socket à l'adresse et au port
    if (bind(listeningSocket, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Erreur lors du bind : " << WSAGetLastError() << std::endl;
        closesocket(listeningSocket);
        WSACleanup();
        return 1;
    }

    // Passage en mode écoute
    if (listen(listeningSocket, SOMAXCONN) == SOCKET_ERROR) {
        std::cerr << "Erreur lors du listen : " << WSAGetLastError() << std::endl;
        closesocket(listeningSocket);
        WSACleanup();
        return 1;
    }

    std::cout << "Serveur multi-client en écoute sur le port 3000..." << std::endl;

    // Vector pour stocker les threads créés (facultatif, pour pouvoir les rejoindre plus tard)
    std::vector<std::thread> threads;

    while (true) {
        sockaddr_in clientAddr;
        int clientAddrSize = sizeof(clientAddr);
        SOCKET clientSocket = accept(listeningSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientAddrSize);
        if (clientSocket == INVALID_SOCKET) {
            std::cerr << "Erreur lors de l'accept : " << WSAGetLastError() << std::endl;
            continue;
        }

        std::cout << "Nouveau client connecté." << std::endl;

        // Créer un thread pour gérer la communication avec ce client
        threads.emplace_back(std::thread(handleClient, clientSocket));
    }

    // Optionnel : rejoindre tous les threads avant de fermer le programme
    for (auto& t : threads) {
        if (t.joinable()) {
            t.join();
        }
    }

    closesocket(listeningSocket);
    WSACleanup();
    return 0;
}
