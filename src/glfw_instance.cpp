#include "glfw_instance.hpp"
#include "glfw_window.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>
#include <stdexcept>
#include <string>

GLFWInstance::GLFWInstance()
{
    int err = glfwInit();
    if (err == GLFW_FALSE)
    {
        throw std::runtime_error("Could not initialize GLFW library");
    }
}

GLFWWindow GLFWInstance::createWindow(int width, int height, const std::string& title) const
{
    GLFWWindow window;
    window.windowPtr_ = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

    if (!window.windowPtr_)
    {
        throw std::runtime_error("Could not create GLFW window");
    }

    return window;
}

GLFWInstance::~GLFWInstance()
{
    glfwTerminate();
}
