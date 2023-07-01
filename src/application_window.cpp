#include "application_window.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <cmath>

ApplicationWindow::ApplicationWindow(int width, int height)
    :
    sf::RenderWindow(sf::VideoMode(width, height), "Convergence visualizer"),
    viewCenter_(2.5, 0),
    viewSize_(10.0, 5.0)
{
    loadShaders();
    setShaderInputs();
    rerender();

    do
    {
        sf::Event e;
        if (!sf::RenderWindow::waitEvent(e))
        {
            throw std::runtime_error("Error while processing window events");
        }

        switch (e.type)
        {
        case sf::Event::Closed:
            sf::RenderWindow::close();
            break;
        case sf::Event::MouseMoved:
            if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
            {
                // TODO
                // pass mouse coordinates into MouseDrag
                // get mouse delta from MouseDrag

                // if mouse delta > 0, add delta to viewCenter_
            }
        case sf::Event::MouseWheelScrolled:
            if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                constexpr float ZOOM_FACTOR = 0.9;
                constexpr float MOVE_FACTOR = 0.2;

                if (e.mouseWheelScroll.delta != 0)
                {
                    sf::Vector2f cursor_pos = toCalcSpaceCoordinates(
                        sf::Vector2u(e.mouseWheelScroll.x, e.mouseWheelScroll.y));

                    viewCenter_ +=
                        (e.mouseWheelScroll.delta < 0 ? -1.f : 1.f)
                        * (cursor_pos - viewCenter_) * MOVE_FACTOR;

                    viewSize_ *= std::pow(ZOOM_FACTOR, e.mouseWheelScroll.delta);

                    setShaderInputs();
                    rerender();
                }
            }
        default:
            break;
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

void ApplicationWindow::setShaderInputs()
{
    sf::Vector2f screen_size = static_cast<sf::Vector2f>(sf::RenderWindow::getSize());
    renderArea_ = sf::RectangleShape(screen_size);
    iterateShader_.setUniform("screenSize", screen_size);
    iterateShader_.setUniform("viewCenter", viewCenter_);
    iterateShader_.setUniform("viewSize", viewSize_);
}

void ApplicationWindow::rerender()
{
    sf::RenderWindow::draw(renderArea_, &iterateShader_);
    sf::RenderWindow::display();
}

sf::Vector2f ApplicationWindow::toCalcSpaceCoordinates(sf::Vector2u window_coord)
{
    auto screen_size = sf::Vector2f(ApplicationWindow::getSize());
    auto normalized_pixel_coord =
        sf::Vector2f(window_coord.x / screen_size.x, 1.0 - window_coord.y / screen_size.y);
    auto x = viewCenter_.x + (normalized_pixel_coord.x - 0.5) * viewSize_.x;
    auto y = viewCenter_.y + (normalized_pixel_coord.y - 0.5) * viewSize_.y;
    return sf::Vector2f(x, y);
}

