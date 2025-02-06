#include "Raquette.h"

Raquette::Raquette() : m_RaquetteSpeed(0.07f), m_RaquettesHeight(150.0f), m_RaquettesWidth(20.0f), m_PlayerIndex(1)
{
    m_RaquetteShape.setSize(sf::Vector2f(m_RaquettesWidth,m_RaquettesHeight));
}

Raquette::~Raquette()
{
}

void Raquette::Update(float WindowHeight, float WindowWidth)
{
	CheckCollision(GetVelocity(),WindowHeight,WindowWidth);
	m_RaquetteShape.setPosition(GetEntityLocation());
}

void Raquette::Draw(sf::RenderWindow& window)
{
	window.draw(m_RaquetteShape);
}

void Raquette::Initialize(float WindowHeight, float WindowWidth)
{
	if (m_PlayerIndex > 1)
	{
		SetEntityLocation(sf::Vector2f(WindowWidth - 10 - m_RaquettesWidth, WindowHeight / 2));
	}
	else
	{
		SetEntityLocation(sf::Vector2f(10, WindowHeight / 2));
	}

}

void Raquette::CheckCollision(sf::Vector2f velocity,float WindowHeight, float WindowWith)
{
		BlockOffset(GetEntityLocation().y + velocity.y < 0 || GetEntityLocation().y + velocity.y + m_RaquettesHeight > WindowHeight);
}

void Raquette::SetPlayerIndex(int index)
{
    m_PlayerIndex = index;
}


int Raquette::GetPlayerIndex()
{
	return m_PlayerIndex;
}

float Raquette::GetRaquetteSpeed()
{
	return m_RaquetteSpeed;
}

float Raquette::GetRaquetteHeight()
{
	return m_RaquettesHeight;
}

float Raquette::GetRaquetteWidth()
{
	return m_RaquettesWidth;
}
