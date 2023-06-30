#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class ApplicationWindow : protected sf::Window
{
public:

    // creates window and enters event processing loop, blocks until window is
    // closed
    ApplicationWindow(int width, int height);

private:

    void rerender();

    sf::RectangleShape renderArea_;
};

