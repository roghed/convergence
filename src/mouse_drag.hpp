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
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <optional>

class MouseDrag
{
public:

    // checks whether user has dragged the mouse, based on this and previous
    // window mouse events
    // if user has dragged the mouse returns a sf::Vector<int> with the cursor
    // delta position (difference between the last known mouse position and the
    // current position)
    // else returns null optional
    std::optional<sf::Vector2i> getDragEvent(const sf::Event& mouse_event);

private:

    bool         isLeftButtonPressed_ = false;
    sf::Vector2i lastCursorPosition_;
};

