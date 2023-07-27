#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <string>

class InputWindow : public sf::RenderWindow
{
public:

    InputWindow(int width, int height, std::string init_text = "");

    void processEvents();
    using sf::RenderWindow::isOpen;

    bool textChanged();
    std::string text();

private:

    void processInputCharacter(char);
    void updateDisplayText();
    void rerender();

    bool textChanged_ = false;
    std::string textString_;
    sf::Font    displayFont_;
    sf::Text    displayText_;
};
