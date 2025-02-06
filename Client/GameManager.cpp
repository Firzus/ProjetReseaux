#include "GameManager.h"

//Constructeur
GameManager::GameManager() : m_PlayerIndex(0), scoreJ1(0), scoreJ2(0)
{
}
//Destructeur
GameManager::~GameManager()
{
}

// Retourne le Scrore du joueur 1
int GameManager::GetScoreJ1()
{
    return scoreJ1;
}
// retourne le Score du joueur 2
int GameManager::GetScoreJ2()
{
    return scoreJ2;
}

// Appelle la fonction " Draw " de chaque entité stocker
void GameManager::Draw(sf::RenderWindow& window)
{
    for (size_t i = 0; i < m_Entitties.size(); i++)
    {
        m_Entitties[i]->Draw(window);
    }
}
// Appelle la fonction " Initialise " de chaque entité stocker
void GameManager::Initialise(float WindowHeight, float WindowWidth)
{
    for (size_t i = 0; i < m_Entitties.size(); i++)
    {
        m_Entitties[i]->Initialize(WindowHeight,WindowWidth);
    }
}
// Appelle la fonction " Update " de chaque entité stocker
void GameManager::Update(float WindowHeight, float WindowWidth)
{
    for (size_t i = 0; i < m_Entitties.size(); i++)
    {
        if (dynamic_cast<Ball*>(m_Entitties[i])) 
        {
            dynamic_cast<Ball*>(m_Entitties[i])->CheckCollisionRaquette(m_Raquettes);
            if (dynamic_cast<Ball*>(m_Entitties[i])->GetWinJ1())
            {
                scoreJ1++;
                Win(WindowHeight,WindowWidth);
            }           
            if (dynamic_cast<Ball*>(m_Entitties[i])->GetWinJ2())
            {
                scoreJ2++;
                Win(WindowHeight, WindowWidth);
            }
        }
        m_Entitties[i]->Update(WindowHeight, WindowWidth);
    }
    CheckBtn(WindowHeight,WindowWidth);
}

// Ajoute une entité au vecteur Entitties !! si l'entiter est une raquette on augmentera l'index du joueur et on l'ascosiera a la raquette !!
void GameManager::AddEntity(Entity* entity)
{

    if (dynamic_cast<Raquette*>(entity)) {
        m_PlayerIndex++;
        dynamic_cast<Raquette*>(entity)->SetPlayerIndex(m_PlayerIndex);
        m_Raquettes.push_back(dynamic_cast<Raquette*>(entity));
    }
    m_Entitties.push_back(entity);
}

void GameManager::CheckBtn(float WindowHeight, float WindowWidth)
{
    // Raquette gauche
    if (m_input.GetButton().Z)
    {
        m_Raquettes[0]->AddEntityOffest(sf::Vector2f(0.0f, -1.0f) * m_Raquettes[0]->GetRaquetteSpeed());
    }
    if (m_input.GetButton().S)
    {
        m_Raquettes[0]->AddEntityOffest(sf::Vector2f(0.0f, 1.0f) * m_Raquettes[0]->GetRaquetteSpeed());
    }
}

void GameManager::SetInput(Input& input)
{
    m_input = input;
}

void GameManager::Win(float WindowHeight, float WindowWidth)
{
    for (size_t i = 0; i < m_Entitties.size(); i++)
    {
        m_Entitties[i]->Initialize(WindowHeight, WindowWidth);
    }
}

// retourn le vecteur d'entité
std::vector<Entity*> GameManager::GetEntitties()
{
    return m_Entitties;
}