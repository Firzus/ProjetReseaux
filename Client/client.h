// Client.cpp
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>
#include <thread>
#include <cstring>
#include "input.h"
#include <SFML/Graphics.hpp>


#pragma comment(lib, "ws2_32.lib") // Lier la bibliothèque Winsock

// Constante
const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

// Prototypes
void CheckBtn();
void UpdateBall();