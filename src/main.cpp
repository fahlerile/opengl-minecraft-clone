#include <iostream>
#include <GLFW/glfw3.h>
#include "Window/Window.hpp"
#include "Application/Application.hpp"

void initialize_glfw();

int main()
{
    initialize_glfw();
    Window window(800, 600, "hello");
    Application app(&window);
    app.start_loop();
    glfwTerminate();
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