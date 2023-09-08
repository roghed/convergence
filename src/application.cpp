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

#include "application.hpp"
#include "main_window.hpp"
#include "input_window.hpp"
#include <exprtk.hpp>
#include <boost/math/constants/constants.hpp>
#include <cmath>
#include <string>
#include <filesystem>
#include <fstream>
#include <regex>
#include <thread>
#include <chrono>
#include <iostream>

Application::Application()
    :
    resLoc_("convergence", "data"),
    rawShaderCode_(getFileContents(resLoc_.locate("iterate_frag.glsl"))),
    mainWin_(800, 600, font_, iterateShader_),
    inputWin_(300, 100, font_, "exp(x) - 1.0 / x")
{
    if (!font_.loadFromFile(resLoc_.locate("UbuntuMono-Regular.ttf").string()))
    {
        throw std::runtime_error("Font loading failed");
    }

    updateShaderFunction();
}

void Application::execute()
{
    using namespace std::chrono;

    while (mainWin_.isOpen() && inputWin_.isOpen())
    {
        auto frame_beg = high_resolution_clock::now();

        mainWin_.processEvents();
        inputWin_.processEvents();

        if (inputWin_.textChanged())
        {
            updateShaderFunction();
        }

        constexpr auto POLL_RATE = milliseconds(4);
        std::this_thread::sleep_until(frame_beg + POLL_RATE);
    }
}

std::string Application::getFileContents(const std::filesystem::path& file_path)
{
    std::string contents;
    std::ifstream stream(file_path);

    if (stream.is_open())
    {
        // get the size of the file
        stream.seekg(0, std::ios::end);
        std::streamsize fileSize = stream.tellg();
        stream.seekg(0, std::ios::beg);

        // read the entire file contents into the string
        contents.resize(fileSize);
        stream.read(&contents[0], fileSize);

        // close the file stream
        stream.close();
    }
    else
    {
        throw std::runtime_error("Unable to open file: " + file_path.string());
    }

    return contents;
}

float Application::calculateFunctionLimit(const std::string& expr_string)
{
    float x;

    exprtk::symbol_table<float> symbol_table;
    symbol_table.add_variable("x", x);
    symbol_table.add_constants();

    exprtk::expression<float> expression;
    expression.register_symbol_table(symbol_table);

    exprtk::parser<float> parser;
    parser.compile(expr_string, expression);

    // Newton–Raphson method with numerical derivative approximation, i.e:
    // df(x)/dx ~= (f(x + h) - f(x)) / h
    constexpr auto N_ITERATIONS = 100;
    constexpr auto H = 1e-6f;
    static const auto X0 = std::sqrt(2) + boost::math::constants::pi<double>();
    float xi = (float)X0;

    for (int i = 0; i < N_ITERATIONS; ++i)
    {
        x = xi;
        auto f_xi = expression.value();

        x = xi + H;
        auto f_xi_h = expression.value();

        xi -= H * f_xi / (f_xi_h - f_xi);
    }

    return xi;
}

void Application::updateShaderFunction()
{
    auto f_expression = inputWin_.text();
    recompileShader(f_expression);
    auto f_limit = calculateFunctionLimit(f_expression);
    mainWin_.setFunctionLimit(f_limit);
    mainWin_.refresh();
}

void Application::recompileShader(const std::string& f_expression)
{
    static const std::string REPLACE_MARKER = "@\\[REPLACE ME\\]@";
    static const std::regex  REPLACE_REGEX(REPLACE_MARKER);

    // TODO: validate inputWin_.text()

    auto altered_shader_code = std::regex_replace(rawShaderCode_, REPLACE_REGEX, f_expression);
    if (!iterateShader_.loadFromMemory(altered_shader_code, sf::Shader::Fragment))
    {
        std::clog << "Shader compilation failed" << std::endl;
    }
}
