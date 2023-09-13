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

#include "mouse_drag.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>
#include <optional>

std::optional<sf::Vector2i> MouseDrag::getDragEvent(const sf::Event& event)
{
    switch (event.type)
    {
    case sf::Event::MouseButtonPressed:
        if (event.mouseButton.button == sf::Mouse::Left)
        {
            lastCursorPosition_ = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
            isLeftButtonPressed_ = true;
        }
        break;
    case sf::Event::MouseMoved:
        if (isLeftButtonPressed_)
        {
            auto cursor_pos = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
            auto cursor_delta = cursor_pos - lastCursorPosition_;

            if (cursor_delta != sf::Vector2i(0, 0))
            {
                lastCursorPosition_ = cursor_pos;
                return cursor_delta;
            }
        }
        break;
    case sf::Event::MouseButtonReleased:
        if (event.mouseButton.button == sf::Mouse::Left)
        {
           isLeftButtonPressed_ = false;
        }
        break;
    default:
        break;
    }

    return std::nullopt;
}
