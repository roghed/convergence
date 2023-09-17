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

#pragma once
#include <SFML/Config.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Color.hpp>
#include <string>

class InputWindow : public sf::RenderWindow
{
public:

    InputWindow(int width, int height, const sf::Font& font, std::string init_text = "");

    void setTextColor(const sf::Color& color);
    void processEvents();
    using sf::RenderWindow::isOpen;

    bool textChanged();
    std::string text();

private:

    void processInputCharacter(sf::Uint32);
    void updateDisplayText();
    void updateDisplayCursor();
    void rerender();

    int                cursorPosition_ = 0;
    bool               textChanged_ = false;
    std::string        textString_;
    const sf::Font&    displayFont_;
    sf::Text           displayText_;
    sf::RectangleShape cursor_;
};
