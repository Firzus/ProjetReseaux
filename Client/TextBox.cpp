#include "TextBox.h"
#include "TextMessage.h"

TextBox::TextBox(sf::Vector2f position, sf::Vector2f size, sf::Font& font, TextMessage& textMessage,
    const std::string& initialText, CharType charType)
    : m_text(font), m_textMessage(textMessage), m_charType(charType)
{
    m_box.setSize(size);
    m_box.setPosition(position);
    m_box.setFillColor(sf::Color::White);
    m_box.setOutlineThickness(2);

    m_text.setFont(font);
    m_stringtext = initialText;
    m_text.setString(m_stringtext);
    m_text.setCharacterSize(20);
    m_text.setFillColor(sf::Color::Black);
    m_text.setPosition(position);

    updateColor();
}

void TextBox::handleEvent(const sf::Event& event, const sf::Vector2f& mousePos)
{
    if (event.is<sf::Event::MouseButtonPressed>()) {
        if (m_box.getGlobalBounds().contains(mousePos)) {
            m_state = State::Focused;
        }
        else {
            m_state = State::Normal;
            m_text.setString(m_stringtext);
            hasFocused = false;
        }
        updateColor();
    }

    if (m_state == State::Focused && event.is<sf::Event::TextEntered>())
    {
        if (!hasFocused) {
            m_text.setString("");
            hasFocused = true;
        }
        char enteredChar = static_cast<char>(event.getIf<sf::Event::TextEntered>()->unicode);
        std::string str = m_text.getString();

        if (enteredChar == 8) { // Backspace
            if (!str.empty()) {
                str.pop_back();
                m_text.setString(str);
            }
        }
        else if (enteredChar == 13) { // Enter
            if (!str.empty())
            {
                m_stockedtext = str;
                std::cout << getText() << std::endl;
                m_text.setString(m_stringtext);
                hasFocused = false;

                if (m_callback)
                {
                    m_callback();
                }

                m_textMessage.SetString(m_stockedtext);  // Mettre à jour TextMessage
            }
        }
        else if (enteredChar >= 32 && enteredChar <= 126 && str.size() < maxChar)
        {
            if (isValidChar(enteredChar)) {  // Vérification avec `isValidChar()`
                str += enteredChar;
                m_text.setString(str);
            }
        }
    }
}

bool TextBox::isValidChar(char enteredChar)
{
    switch (m_charType) {
    case CharType::Letter:
        return std::isalpha(enteredChar);  // Autoriser uniquement les lettres
    case CharType::Number:
        return std::isdigit(enteredChar);  // Autoriser uniquement les chiffres
    case CharType::IPAddress:
        return (std::isdigit(enteredChar) || enteredChar == '.');  // Chiffres et points
    default:
        return false;
    }
}

void TextBox::updateState(const sf::Vector2f& mousePos)
{
    if (m_state != State::Focused) { // On ne change pas l'état si déjà en focus
        m_state = m_box.getGlobalBounds().contains(mousePos) ? State::Hovered : State::Normal;
        updateColor();
    }
}

void TextBox::updateColor()
{
    switch (m_state) {
    case State::Normal:
        m_box.setOutlineColor(sf::Color::Black);
        break;
    case State::Hovered:
        m_box.setOutlineColor(sf::Color::Green);
        break;
    case State::Focused:
        m_box.setOutlineColor(sf::Color::Blue);
        break;
    }
}

void TextBox::draw(sf::RenderWindow& window)
{
    window.draw(m_box);
    window.draw(m_text);
}

std::string TextBox::getText() const
{
    return m_stockedtext;
}
