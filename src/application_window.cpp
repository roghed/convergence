#include "application_window.hpp"
#include <SFML/Window.hpp>

ApplicationWindow::ApplicationWindow(int width, int height)
    :
    sf::RenderWindow(sf::VideoMode(width, height), "Convergence visualizer"),
    renderArea_(sf::Vector2f(width, height))
{
    loadShaders();
    iterateShader_.setUniform("screenSize", sf::Vector2f(width, height));
    rerender();

    do
    {
        sf::Event e;
        if (!sf::RenderWindow::waitEvent(e))
        {
            throw std::runtime_error("Error while processing window events");
        }

        if (e.type == sf::Event::Closed)
        {
            sf::RenderWindow::close();
        }

    } while (sf::RenderWindow::isOpen());
}

void ApplicationWindow::loadShaders()
{
    if (!iterateShader_.loadFromFile("shaders/iterate_frag.glsl", sf::Shader::Fragment))
    {
        throw std::runtime_error("Could not load shader");
    }
}

void ApplicationWindow::rerender()
{
    sf::RenderWindow::draw(renderArea_, &iterateShader_);
    sf::RenderWindow::display();
}

