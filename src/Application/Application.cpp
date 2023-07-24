#include <iostream>
#include <cstdlib>

#define GLEW_STATIC
#include <GL/glew.h>

#include "Application.hpp"
#include "Window/Window.hpp"

Application::Application(Window* window) : renderer()
{
    this->window = window;
    this->initialize_glew();
    this->load_resources();

    // TODO: delete this somewhere
    ModelRenderer *plane = new ModelRenderer(
        {
            -1.0f,  1.0f,  0.0f,   0.0f, 1.0f,
             1.0f,  1.0f,  0.0f,   1.0f, 1.0f,
            -1.0f, -1.0f,  0.0f,   0.0f, 0.0f,
             1.0f, -1.0f,  0.0f,   1.0f, 0.0f,
        },
        {
            0, 1, 2,
            1, 2, 3
        }
    );
    plane->add_position(glm::vec3(0.0f, 0.0f, 0.0f));

    this->renderer.add(plane);
}

Application::~Application()
{
    this->quit(0);
}

void Application::initialize_glew()
{
    // initialize GLEW
    if (glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        this->quit(2);
    }
}

void Application::load_resources()
{

}

void Application::start_loop()
{
    while (!glfwWindowShouldClose(this->window->get_id()))
    {
        glClearColor(0.1f, 0.1f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->renderer.submit();

        glfwSwapBuffers(this->window->get_id());
        glfwPollEvents();
    }
}

void Application::quit(int code)
{
    glfwTerminate();
    exit(code);
}