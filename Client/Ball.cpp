#include "Ball.h"

Ball::Ball() : m_SimulatePhysic(false), m_ballRadius(15), m_ballSpeed(0.03f), m_ballPosX(0), m_ballPosY(0)
{
	m_BallShape.setRadius(m_ballRadius);
}

Ball::~Ball()
{
}

void Ball::Update(float WindowHeight, float WindowWidth)
{
	if (m_SimulatePhysic) 
	{
		CheckCollision(GetVelocity(), WindowHeight, WindowWidth);
		AddEntityOffest(m_ballDir * m_ballSpeed);
	}

	m_BallShape.setPosition(GetEntityLocation());
}

void Ball::Draw(sf::RenderWindow& window)
{
	window.draw(m_BallShape);
}

void Ball::Initialize(float WindowHeight, float WindowWidth)
{
	m_SimulatePhysic = true;
	SetEntityLocation(sf::Vector2f(WindowHeight / 2 , WindowWidth / 2));
	m_ballDir = sf::Vector2f(2.0f,0.7f);
}

void Ball::CheckCollision(sf::Vector2f velocity, float WindowHeight, float WindowWidth)
{
	if (GetEntityLocation().y + velocity.y <= 0 || GetEntityLocation().y + velocity.y > WindowHeight)
	{
		m_ballDir.y *= -1.0f;
	}
	if (GetEntityLocation().x + velocity.x <= 0 || GetEntityLocation().x + velocity.x > WindowWidth)
	{
		m_ballDir.x *= -1.0f;
	}
}
