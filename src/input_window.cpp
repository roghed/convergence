#include "input_window.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <cctype>

InputWindow::InputWindow(int width, int height, std::string init_text) :
    sf::RenderWindow(sf::VideoMode(width, height), "Convergence visualizer"),
    textString_(init_text)
{
    displayFont_.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf");
    displayText_.setFont(displayFont_);
    displayText_.setCharacterSize(15);
    displayText_.setString(textString_);
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
        case sf::Event::Resized:
        {
            auto s = sf::Vector2f(e.size.width, e.size.height);
            auto v = sf::View(s * 0.5f, s);
            sf::RenderWindow::setView(v);
        }
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
        textString_.push_back(c);
        updateDisplayText();
    }
    else if (c == BACKSPACE)
    {
        if (!textString_.empty())
        {
            textString_.pop_back();
            updateDisplayText();
        }
    }
}

void InputWindow::updateDisplayText()
{
    displayText_.setString(textString_);
    textChanged_ = true;
}

void InputWindow::rerender()
{
    sf::RenderWindow::clear();
    sf::RenderWindow::draw(displayText_);
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
