/* Copyright (C) 2023 Jan Rogowski

This file is part of Convergence.

Convergence is free software: you can redistribute it and/or modify it under the
terms of the GNU General Public License as published by the Free Software
Foundation, either version 3 of the License, or (at your option) any later
version.

Convergence is distributed in the hope that it will be useful, but WITHOUT ANY
WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A
PARTICULAR PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with
Convergence. If not, see <https://www.gnu.org/licenses/>.*/

#pragma once
#include "mouse_drag.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/System/Vector2.hpp>
#include <string>
#include <vector>

class MainWindow : protected sf::RenderWindow
{
public:

    MainWindow(int width, int height, const sf::Font& font, sf::Shader& iterate_shader);

    void processEvents();
    using sf::RenderWindow::isOpen;
    void refresh();
    void setFunctionLimit(float value);
    using sf::RenderWindow::setIcon;

private:

    void recalculateGrid();
    void setShaderInputs();
    void rerender();

    sf::Vector2f toCalcSpaceCoordinates(sf::Vector2i window_coord) const;
    sf::Vector2i toWindowSpaceCoordinates(sf::Vector2f calc_space_coord) const;

    static std::string getLabelString(int coefficient, float grid_scale);

    MouseDrag               mouseDrag_;
    sf::RectangleShape      renderArea_;
    sf::Shader*             ptrIterateShader_;
    sf::Vector2f            viewCenter_;
    sf::Vector2f            viewSize_;
    float                   gridScale_;
    float                   functionLimit_;
    const sf::Font&         labelsFont_;
    std::vector<sf::Text>   xAxisLabels_;
    std::vector<sf::Text>   yAxisLabels_;
    bool                    doRerender_ = false;
};

