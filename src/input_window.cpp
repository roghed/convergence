/* Copyright (C) 2023 Jan Rogowski

This file is part of Convergence.

Convergence is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

Convergence is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
Convergence. If not, see <https://www.gnu.org/licenses/>.*/

#include "input_window.hpp"
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Vector2.hpp>
#include <cctype>
#include <utility>

InputWindow::InputWindow(int width, int height, const sf::Font& font, std::string init_text) :
    sf::RenderWindow(sf::VideoMode(width, height), "Convergence visualizer"),
    textString_(init_text),
    displayFont_(font),
    cursor_(sf::Vector2f(1, 15))
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
                cursorPosition_ = std::min<int>(cursorPosition_ + 1, (int)textString_.length());
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
            auto s = sf::Vector2f((float)e.size.width, (float)e.size.height);
            auto v = sf::View(s * 0.5f, s);
            sf::RenderWindow::setView(v);
        }
            [[fallthrough]];
        case sf::Event::GainedFocus:
            [[fallthrough]];
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

void InputWindow::processInputCharacter(sf::Uint32 c)
{
    static constexpr char BACKSPACE = '\b';

    if ((std::isgraph(c)) || c == ' ')
    {
        textString_.insert(cursorPosition_++, 1, (char)c);
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
