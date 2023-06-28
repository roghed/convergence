#pragma once
#include <string>

//class GLFWInstance;
class GLFWwindow;

class GLFWWindow
{
public:

    GLFWWindow(GLFWWindow&& other);
    ~GLFWWindow();

    friend class GLFWInstance;

private:

    GLFWWindow() = default;

    GLFWwindow* windowPtr_ = nullptr;
};

