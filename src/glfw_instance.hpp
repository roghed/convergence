#pragma once
#include <string>

class GLFWWindow;

class GLFWInstance
{
public:

    GLFWInstance();

    GLFWWindow createWindow(int width, int height, const std::string& title) const;

    ~GLFWInstance();
};

