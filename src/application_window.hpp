#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shader.hpp>

class ApplicationWindow : protected sf::RenderWindow
{
public:

    // creates window and enters event processing loop, blocks until window is
    // closed
    ApplicationWindow(int width, int height);

private:

    void loadShaders();
    void rerender();

    sf::RectangleShape renderArea_;
    sf::Shader         iterateShader_;
};

