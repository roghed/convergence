#include "application_window.hpp"
#include <SFML/Window.hpp>

ApplicationWindow::ApplicationWindow(int width, int height)
    : sf::Window(sf::VideoMode(width, height), "Convergence visualizer")
{
    rerender();

    do
    {
        sf::Event e;
        if (!sf::Window::waitEvent(e))
        {
            throw std::runtime_error("Error while processing window events");
        }

        if (e.type == sf::Event::Closed)
        {
            sf::Window::close();
        }

    } while (sf::Window::isOpen());
}

void ApplicationWindow::rerender()
{

}

