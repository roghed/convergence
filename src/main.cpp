#include <SFML/Window.hpp>
#include <stdexcept>

int main()
{
    sf::Window main_window(sf::VideoMode(800, 600), "Convergence visualizer");
    sf::Event event;
    main_window.display();

    while (main_window.isOpen())
    {
        if (!main_window.waitEvent(event))
        {
            throw std::runtime_error("Unable to poll window events");
        }

        if (event.type == sf::Event::Closed)
        {
            main_window.close();
        }
    }
}
