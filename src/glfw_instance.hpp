#pragma once
#include "glfw_window.hpp"

class GLFWInstance
{
public:

    GLFWInstance();

    GLFWWindow createWindow(int width, int height, const std::string& title) const;

    ~GLFWInstance();
};

