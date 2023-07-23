#include <iostream>
#include <GLFW/glfw3.h>
#include "Application.hpp"

void initialize_glfw();

int main()
{
    initialize_glfw();
    Application app;
    app.start_loop();
    return 0;
}

void initialize_glfw()
{
    // initialize GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW" << std::endl;
        std::exit(1);
    }
}