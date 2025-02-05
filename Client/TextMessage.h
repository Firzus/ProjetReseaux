#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class TextMessage
{

private:

	sf::Text m_text;

public:

	TextMessage(const std::string& text, sf::Color color, sf::Vector2f position, sf::Font& font);

	std::string GetString() { return m_text.getString(); }
	void SetString(std::string newtext) { m_text.setString(newtext); }
	void AddString(std::string stringtoadd) { m_text.setString(m_text.getString() + stringtoadd); }
	void Draw(sf::RenderWindow& window);
	void Update();

};

