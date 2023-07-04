#pragma once
#include "mouse_drag.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Text.hpp>
#include <vector>
#include <string>

class ApplicationWindow : protected sf::RenderWindow
{
public:

    // creates window and enters event processing loop, blocks until window is
    // closed
    ApplicationWindow(int width, int height);

private:

    void loadShaders();
    void loadLabelsFont();
    void recalculateGrid();
    void setShaderInputs();
    void rerender();
    sf::Vector2f toCalcSpaceCoordinates(sf::Vector2i window_coord) const;
    sf::Vector2i toWindowSpaceCoordinates(sf::Vector2f calc_space_coord) const;

    static std::string getLabelString(int coefficient, float grid_scale);

    MouseDrag             mouseDrag_;
    sf::RectangleShape    renderArea_;
    sf::Shader            iterateShader_;
    sf::Vector2f          viewCenter_;
    sf::Vector2f          viewSize_;
    float                 gridScale_;
    sf::Font              labelsFont_;
    std::vector<sf::Text> xAxisLabels_;
    std::vector<sf::Text> yAxisLabels_;
};

