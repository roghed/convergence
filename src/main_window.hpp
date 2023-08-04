#pragma once
#include "mouse_drag.hpp"
#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/RectangleShape.hpp>
#include <SFML/Graphics/Shader.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Font.hpp>
#include <SFML/System/Vector2.hpp>
#include <vector>
#include <string>
#include <condition_variable>
#include <mutex>
#include <future>

class MainWindow : protected sf::RenderWindow
{
public:

    MainWindow(int width, int height, const sf::Font& font, sf::Shader& iterate_shader);
    ~MainWindow();

    void processEvents();
    using sf::RenderWindow::isOpen;
    void refresh();
    void setFunctionLimit(float value);

private:

    void recalculateGrid();
    void setShaderInputs();

    // rendering functions
    void requestRerender();
    void startRenderWorker();
    void killRenderWorker();
    void renderBackgroundWorker();
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
    std::condition_variable rerenderCv_;
    std::mutex				rerenderCvMtx_;
    std::mutex				renderResourcesMtx_;
    std::atomic<bool>       killRenderWorkerFlag_ = false;
    std::future<void>       renderWorkerFut_;
};

