#include "application_window.hpp"
#include <SFML/System/Vector2.hpp>
#include <SFML/Window.hpp>
#include <cmath>
#include <vector>

ApplicationWindow::ApplicationWindow(int width, int height)
    :
    sf::RenderWindow(sf::VideoMode(width, height), "Convergence visualizer"),
    viewCenter_(2.5, 0),
    viewSize_(10.0, 5.0),
    gridScale_(1.0)
{
    loadShaders();
    loadLabelsFont();
    recalculateGrid();
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

                    recalculateGrid();
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

            recalculateGrid();
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

void ApplicationWindow::loadLabelsFont()
{
    // TODO: make font loading portable on every system
    labelsFont_.loadFromFile("/usr/share/fonts/truetype/ubuntu/Ubuntu-R.ttf");
}

void ApplicationWindow::setShaderInputs()
{
    sf::Vector2f screen_size = static_cast<sf::Vector2f>(sf::RenderWindow::getSize());
    renderArea_ = sf::RectangleShape(screen_size);

    iterateShader_.setUniform("screenSize", screen_size);
    iterateShader_.setUniform("viewCenter", viewCenter_);
    iterateShader_.setUniform("viewSize", viewSize_);
    iterateShader_.setUniform("gridScale", gridScale_);
}

void ApplicationWindow::recalculateGrid()
{
    gridScale_ = std::pow(10.0, std::ceil(std::log10(viewSize_.x * 5)) - 2);
    sf::Vector2f view_bot_left = viewCenter_ - viewSize_ * 0.5f;

    xAxisLabels_.resize((int)(viewSize_.x / gridScale_) + 2);
    for (int i = 0; i < xAxisLabels_.size(); ++i)
    {
        auto& label = xAxisLabels_[i];

        label.setFont(labelsFont_);
        label.setCharacterSize(16);
        label.setString("xxx"); // TODO: set to numeric value of the label
        label.setFillColor(sf::Color::Blue);
        label.setOrigin(0, 2 * label.getLocalBounds().height);

        sf::Vector2f pos;
        pos.x = gridScale_ * (std::ceil(view_bot_left.x / gridScale_) + i - 1);
        pos.y = view_bot_left.y;
        sf::Vector2i window_space_pos = toWindowSpaceCoordinates(pos);
        label.setPosition((sf::Vector2f)(window_space_pos));
    }

    yAxisLabels_.resize((int)(viewSize_.y / gridScale_) + 2);
    for (int i = 0; i < yAxisLabels_.size(); ++i)
    {
        auto& label = yAxisLabels_[i];

        label.setFont(labelsFont_);
        label.setCharacterSize(16);
        label.setString("yyy"); // TODO: set to numeric value of the label
        label.setFillColor(sf::Color::Blue);
        label.setOrigin(0, 2 * label.getLocalBounds().height);

        sf::Vector2f pos;
        pos.x = view_bot_left.x;
        pos.y = gridScale_ * (std::ceil(view_bot_left.y / gridScale_) + i - 1);
        sf::Vector2i window_space_pos = toWindowSpaceCoordinates(pos);
        label.setPosition((sf::Vector2f)(window_space_pos));
    }
}

void ApplicationWindow::rerender()
{
    sf::RenderWindow::draw(renderArea_, &iterateShader_);

    for (const auto& label : xAxisLabels_)
    {
        sf::RenderWindow::draw(label);
    }

    for (const auto& label : yAxisLabels_)
    {
        sf::RenderWindow::draw(label);
    }

    sf::RenderWindow::display();
}

sf::Vector2f ApplicationWindow::toCalcSpaceCoordinates(sf::Vector2i window_coord) const
{
    auto screen_size = sf::Vector2f(ApplicationWindow::getSize());
    auto normalized_pixel_coord =
        sf::Vector2f(window_coord.x / screen_size.x, 1.0 - window_coord.y / screen_size.y);
    auto x = viewCenter_.x + (normalized_pixel_coord.x - 0.5) * viewSize_.x;
    auto y = viewCenter_.y + (normalized_pixel_coord.y - 0.5) * viewSize_.y;
    return sf::Vector2f(x, y);
}

sf::Vector2i ApplicationWindow::toWindowSpaceCoordinates(sf::Vector2f calc_space_coord) const
{
    auto screen_size = sf::Vector2f(ApplicationWindow::getSize());
    auto bot_left_corner = viewCenter_ - 0.5f * viewSize_;

    sf::Vector2f result =
    {
        (calc_space_coord.x - bot_left_corner.x) / viewSize_.x * screen_size.x,
        (calc_space_coord.y - bot_left_corner.y) / viewSize_.y * screen_size.y
    };

    result = sf::Vector2f
    {
        ((calc_space_coord.x - viewCenter_.x) / viewSize_.x + 0.5f) * screen_size.x,
        ((calc_space_coord.y - viewCenter_.y) / viewSize_.y + 0.5f) * screen_size.y
    };

    return {(int)result.x, (int)(screen_size.y - result.y)};
}
