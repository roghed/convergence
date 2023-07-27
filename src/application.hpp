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
    void recompileShader();

    MainWindow  mainWin_;
    InputWindow inputWin_;
    sf::Shader  iterateShader_;
    std::string rawShaderCode_;
};

