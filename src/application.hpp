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
#include "main_window.hpp"
#include "input_window.hpp"
#include <SFML/Graphics/Shader.hpp>
#include <string>
#include <filesystem>

class Application
{
public:

    Application();
    void execute();

private:

    static std::string getFileContents(const std::filesystem::path&);
    static float calculateFunctionLimit(const std::string& f_expression);

    void updateShaderFunction();
    void recompileShader(const std::string& f_expression);

    std::string rawShaderCode_;
    sf::Shader  iterateShader_;
    sf::Font    font_;
    MainWindow  mainWin_;
    InputWindow inputWin_;
};

