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
        case sf::Event::MouseWheelScrolled:
            if (e.mouseWheelScroll.wheel == sf::Mouse::VerticalWheel)
            {
                constexpr float ZOOM_FACTOR = 0.9;
                constexpr float MOVE_FACTOR = 0.2;

                if (e.mouseWheelScroll.delta != 0)
                {
                    auto cursor_window_pos = sf::Vector2i(e.mouseWheelScroll.x, e.mouseWheelScroll.y);
                    sf::Vector2f cursor_calc_space_pos = toCalcSpaceCoordinates(cursor_window_pos);

                    viewCenter_ +=
                        (e.mouseWheelScroll.delta < 0 ? -1.f : 1.f)
                        * (cursor_calc_space_pos - viewCenter_) * MOVE_FACTOR;

                    viewSize_ *= std::pow(ZOOM_FACTOR, e.mouseWheelScroll.delta);

                    setShaderInputs();
                    rerender();
                }
            }
            break;
        default:
            break;
        }

        if (auto drag_event = mouseDrag_.getDragEvent(e); drag_event.has_value())
        {
            auto window_space_delta = drag_event.value();
            auto calc_space_origin = toCalcSpaceCoordinates(sf::Vector2i(0, 0));
            auto calc_space_delta = toCalcSpaceCoordinates(window_space_delta) - calc_space_origin;

            viewCenter_ -= calc_space_delta;

            setShaderInputs();
            rerender();
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
    float grid_scale = std::pow(10.0, std::ceil(std::log10(viewSize_.x * 5)) - 2);

    iterateShader_.setUniform("screenSize", screen_size);
    iterateShader_.setUniform("viewCenter", viewCenter_);
    iterateShader_.setUniform("viewSize", viewSize_);
    iterateShader_.setUniform("gridScale", grid_scale);
}

void ApplicationWindow::rerender()
{
    sf::RenderWindow::draw(renderArea_, &iterateShader_);
    sf::RenderWindow::display();
}

sf::Vector2f ApplicationWindow::toCalcSpaceCoordinates(sf::Vector2i window_coord)
{
    auto screen_size = sf::Vector2f(ApplicationWindow::getSize());
    auto normalized_pixel_coord =
        sf::Vector2f(window_coord.x / screen_size.x, 1.0 - window_coord.y / screen_size.y);
    auto x = viewCenter_.x + (normalized_pixel_coord.x - 0.5) * viewSize_.x;
    auto y = viewCenter_.y + (normalized_pixel_coord.y - 0.5) * viewSize_.y;
    return sf::Vector2f(x, y);
}

