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
    void setShaderInputs();
    void rerender();
    sf::Vector2f toCalcSpaceCoordinates(sf::Vector2u window_coord);

    sf::RectangleShape renderArea_;
    sf::Shader         iterateShader_;
    sf::Vector2f       viewCenter_;
    sf::Vector2f       viewSize_;
};

