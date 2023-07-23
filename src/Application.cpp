#include <iostream>
#include <cstdlib>

#define GLEW_STATIC
#include <GL/glew.h>

#include "Application.hpp"
#include "Window.hpp"

Application::Application() : window(800, 600, "Hello, cube!")
{
    this->initialize_glew();
    this->load_resources();
}

Application::~Application()
{
    glfwTerminate();
}

void Application::initialize_glew()
{
    // initialize GLEW
    if (glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        glfwTerminate();
        std::exit(2);
    }
}

void Application::load_resources()
{

}

void Application::start_loop()
{
    while (!glfwWindowShouldClose(this->window.get_id()))
    {
        glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glfwSwapBuffers(this->window.get_id());
        glfwPollEvents();
    }
}