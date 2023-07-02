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

