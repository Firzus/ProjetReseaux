#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>

class Input
{
public:
    // Structure pour les états des boutons
    struct Button {
        bool left, right, up, down, escape;
    };

    // Constructeur
    Input();

    // Getter pour l'état des boutons
    Button GetButton(void) const;

    // Gestion des entrées
    void InputHandler(const sf::Event& event, sf::RenderWindow& window);

private:
    // Instance de la structure Button
    Button m_button;
};

#endif // INPUT_H