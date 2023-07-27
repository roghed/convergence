#include "application.hpp"
#include "main_window.hpp"
#include "input_window.hpp"
#include <string>
#include <filesystem>
#include <fstream>
#include <regex>

Application::Application()
    : mainWin_(800, 600, iterateShader_), inputWin_(300, 100, "exp(x) - 1.0 / x")
{
    rawShaderCode_ = getFileContents("shaders/iterate_frag.glsl");
    recompileShader();
}

void Application::execute()
{
    while (mainWin_.isOpen() && inputWin_.isOpen())
    {
        mainWin_.processEvents();
        inputWin_.processEvents();

        if (inputWin_.textChanged())
        {
            recompileShader();
        }
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

void Application::recompileShader()
{
    static const std::string REPLACE_MARKER = "@[REPLACE ME]@";
    static const std::regex  REPLACE_REGEX(REPLACE_MARKER);

    // TODO: validate inputWin_.text()

    auto altered_shader_code = std::regex_replace(rawShaderCode_, REPLACE_REGEX, inputWin_.text());
    if (!iterateShader_.loadFromMemory(altered_shader_code, sf::Shader::Fragment))
    {
        throw std::runtime_error("Shader compilation failed");
    }
}
