#pragma once
#include "glfw_instance.hpp"
#include <string>

class GLFWwindow;

class GLFWWindow
{
public:

    GLFWWindow(GLFWWindow&& other);
    ~GLFWWindow();

    friend GLFWWindow GLFWInstance::createWindow(int width, int height, const std::string& title) const;

private:

    GLFWWindow() = default;

    GLFWwindow* windowPtr_ = nullptr;
};

