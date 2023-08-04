#include "input_window.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <cctype>
#include <utility>

InputWindow::InputWindow(int width, int height, const sf::Font& font, std::string init_text) :
    sf::RenderWindow(sf::VideoMode(width, height), "Convergence visualizer"),
    textString_(init_text),
    cursor_(sf::Vector2f(1, 15)),
    displayFont_(font)
{
    displayText_.setFont(displayFont_);
    displayText_.setCharacterSize(15);
    displayText_.setString(textString_);
    updateDisplayCursor();
    rerender();
}

void InputWindow::processEvents()
{
    sf::Event e;

    while (sf::RenderWindow::pollEvent(e))
    {
        switch (e.type)
        {
        case sf::Event::Closed:
            sf::RenderWindow::close();
            break;
        case sf::Event::TextEntered:
            processInputCharacter(e.text.unicode);
            break;
        case sf::Event::KeyPressed:
            if (e.key.code == sf::Keyboard::Right)
            {
                cursorPosition_ = std::min<int>(cursorPosition_ + 1, textString_.length());
                updateDisplayCursor();
                rerender();
            }
            else if (e.key.code == sf::Keyboard::Left)
            {
                cursorPosition_ = std::max<int>(cursorPosition_ - 1, 0);
                updateDisplayCursor();
                rerender();
            }
            break;
        case sf::Event::Resized:
        {
            auto s = sf::Vector2f(e.size.width, e.size.height);
            auto v = sf::View(s * 0.5f, s);
            sf::RenderWindow::setView(v);
        }
        case sf::Event::GainedFocus:
        case sf::Event::MouseEntered:
            rerender();
            break;
        default:
            break;
        }
    }

    if (textChanged_)
    {
        rerender();
    }
}

void InputWindow::processInputCharacter(char c)
{
    static constexpr char BACKSPACE = '\b';

    if ((std::isgraph(c)) || c == ' ')
    {
        textString_.insert(cursorPosition_++, 1, c);
        updateDisplayText();
        updateDisplayCursor();
    }
    else if (c == BACKSPACE && cursorPosition_ != 0)
    {
        textString_.erase(--cursorPosition_, 1);
        updateDisplayText();
        updateDisplayCursor();
    }
}

void InputWindow::updateDisplayText()
{
    displayText_.setString(textString_);
    textChanged_ = true;
}

void InputWindow::updateDisplayCursor()
{
    cursor_.setPosition(displayText_.findCharacterPos(cursorPosition_));
}

void InputWindow::rerender()
{
    sf::RenderWindow::clear();
    sf::RenderWindow::draw(displayText_);
    sf::RenderWindow::draw(cursor_);
    sf::RenderWindow::display();
}

bool InputWindow::textChanged()
{
    return textChanged_;
}

std::string InputWindow::text()
{
    textChanged_ = false;
    return textString_;
}
