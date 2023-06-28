#include "glfw_instance.hpp"
#include "glfw_window.hpp"
#include <iostream>
#include <thread>

int main()
{
    GLFWInstance glfw_instance;
    auto window = glfw_instance.createWindow(800, 600, "Convergence visualizer");
    std::this_thread::sleep_for(std::chrono::seconds(5));
}
