#include "glfw_window.hpp"
#include <GL/gl.h>
#include <GLFW/glfw3.h>

GLFWWindow::GLFWWindow(GLFWWindow&& other)
{
    this->windowPtr_ = other.windowPtr_;
    other.windowPtr_ = nullptr;
}

GLFWWindow::~GLFWWindow()
{
    glfwDestroyWindow(windowPtr_);
}
