// Serveur.cpp
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

#pragma comment(lib, "ws2_32.lib")

#define DEFAULT_PORT "3000"

int main() {
    // Initialisation de Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Erreur WSAStartup" << std::endl;
        return 1;
    }

    // Création d'un socket TCP/IP
    SOCKET listeningSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listeningSocket == INVALID_SOCKET) {
        std::cerr << "Erreur lors de la création du socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Configuration de l'adresse du serveur
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;  // Écoute sur toutes les interfaces
    serverAddr.sin_port = htons(3000);         // Port d'écoute (à choisir)

    // Liaison du socket avec l'adresse et le port
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

    std::cout << "Serveur en attente de connexions sur le port 3000..." << std::endl;

    // Acceptation d'une connexion entrante
    sockaddr_in clientAddr;
    int clientSize = sizeof(clientAddr);
    SOCKET clientSocket = accept(listeningSocket, reinterpret_cast<sockaddr*>(&clientAddr), &clientSize);
    if (clientSocket == INVALID_SOCKET) {
        std::cerr << "Erreur lors de l'accept : " << WSAGetLastError() << std::endl;
        closesocket(listeningSocket);
        WSACleanup();
        return 1;
    }

    // Réception de données du client
    const int bufferSize = 4096;
    char buffer[bufferSize];
    ZeroMemory(buffer, bufferSize);
    int bytesReceived = recv(clientSocket, buffer, bufferSize, 0);
    if (bytesReceived > 0) {
        std::cout << "Message reçu : " << buffer << std::endl;
    }
    else if (bytesReceived == 0) {
        std::cout << "La connexion a été fermée par le client." << std::endl;
    }
    else {
        std::cerr << "Erreur lors de la réception : " << WSAGetLastError() << std::endl;
    }

    // Envoi d'une réponse au client
    const char* reply = "Message reçu!";
    send(clientSocket, reply, static_cast<int>(strlen(reply)), 0);

    // Fermeture des sockets
    closesocket(clientSocket);
    closesocket(listeningSocket);
    WSACleanup();

    return 0;
}
