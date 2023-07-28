#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
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
    void updateDisplayCursor();
    void rerender();

    int                cursorPosition_ = 0;
    bool               textChanged_ = false;
    std::string        textString_;
    sf::Font           displayFont_;
    sf::Text           displayText_;
    sf::RectangleShape cursor_;
};
