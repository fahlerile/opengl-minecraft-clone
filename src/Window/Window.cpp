#include <iostream>
#include <cstdlib>

#include "Window.hpp"

Window::Window(unsigned int width, unsigned int height, const char *title)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    this->id = glfwCreateWindow(width, height, title, NULL, NULL);
    if (this->id == NULL)
    {
        std::cout << "Failed to create a window" << std::endl;
        glfwTerminate();
        std::exit(3);
    }
    glfwMakeContextCurrent(this->id);
}

GLFWwindow* Window::get_id()
{
    return this->id;
}