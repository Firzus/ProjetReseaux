// Client.cpp
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <cstring>

#pragma comment(lib, "ws2_32.lib")

int main() {
    // Initialisation de Winsock
    WSADATA wsaData;
    if (WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) {
        std::cerr << "Erreur WSAStartup" << std::endl;
        return 1;
    }

    // Création d'un socket TCP/IP
    SOCKET sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sock == INVALID_SOCKET) {
        std::cerr << "Erreur lors de la création du socket : " << WSAGetLastError() << std::endl;
        WSACleanup();
        return 1;
    }

    // Configuration de l'adresse du serveur
    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(3000);

    // Conversion de l'adresse IP du serveur (ici localhost, changez-la selon vos besoins)
    if (inet_pton(AF_INET, "127.0.0.1", &serverAddr.sin_addr) <= 0) {
        std::cerr << "Adresse IP invalide" << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Connexion au serveur
    if (connect(sock, reinterpret_cast<sockaddr*>(&serverAddr), sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de la connexion : " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Envoi d'un message au serveur
    const char* message = "Salut serveur!";
    if (send(sock, message, static_cast<int>(strlen(message)), 0) == SOCKET_ERROR) {
        std::cerr << "Erreur lors de l'envoi : " << WSAGetLastError() << std::endl;
        closesocket(sock);
        WSACleanup();
        return 1;
    }

    // Réception de la réponse du serveur
    const int bufferSize = 4096;
    char buffer[bufferSize];
    ZeroMemory(buffer, bufferSize);
    int bytesReceived = recv(sock, buffer, bufferSize, 0);
    if (bytesReceived > 0) {
        std::cout << "Réponse du serveur : " << buffer << std::endl;
    }
    else if (bytesReceived == 0) {
        std::cout << "La connexion a été fermée par le serveur." << std::endl;
    }
    else {
        std::cerr << "Erreur lors de la réception : " << WSAGetLastError() << std::endl;
    }

    // Fermeture du socket
    closesocket(sock);
    WSACleanup();

    return 0;
}
