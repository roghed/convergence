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
    MainWindow  mainWin_;
    InputWindow inputWin_;
};

