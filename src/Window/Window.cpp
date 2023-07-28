#include <iostream>
#include <cstdlib>

#include "Window.hpp"

Window::Window(unsigned int width, unsigned int height, const char *title, bool fullscreen)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

    if (fullscreen)
        this->id = glfwCreateWindow(width, height, title, glfwGetPrimaryMonitor(), NULL);
    else
        this->id = glfwCreateWindow(width, height, title, NULL, NULL);
    if (this->id == NULL)
    {
        std::cout << "Failed to create a window" << std::endl;
        glfwTerminate();
        std::exit(3);
    }
    glfwMakeContextCurrent(this->id);
    glfwSwapInterval(0);
}

GLFWwindow* Window::get_id()
{
    return this->id;
}