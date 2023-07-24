#include <iostream>
#include <cstdlib>
#include <filesystem>

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
            -0.5f,  0.5f,  0.0f,   0.0f, 1.0f,
             0.5f,  0.5f,  0.0f,   1.0f, 1.0f,
            -0.5f, -0.5f,  0.0f,   0.0f, 0.0f,
             0.5f, -0.5f,  0.0f,   1.0f, 0.0f,
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
    // delete this->basic_shader;
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
    // this->basic_shader = new Shader("D:\\Programming\\Projects\\opengl-minecraft-clone\\res\\shaders\\basic\\vertex.glsl",
    //                                 "D:\\Programming\\Projects\\opengl-minecraft-clone\\res\\shaders\\basic\\fragment.glsl");
    // this->basic_shader->use();
}

void Application::start_loop()
{
    while (!glfwWindowShouldClose(this->window->get_id()))
    {
        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
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