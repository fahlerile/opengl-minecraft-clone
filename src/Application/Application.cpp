#include <iostream>
#include <cstdlib>
#include <filesystem>

#define GLEW_STATIC
#include <GL/glew.h>

#include "Application.hpp"
#include "Window/Window.hpp"
#include "callbacks.hpp"

Application::Application(Window* window) : renderer()
{
    this->window = window;
    this->initialize_glew();
    this->load_resources();

    this->camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 5.0f, this->window);

    glfwSetInputMode(this->window->get_id(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(this->window->get_id(), this->camera);
    glfwSetCursorPosCallback(this->window->get_id(), cursor_pos_callback);

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
        },

        "D:\\Programming\\Projects\\opengl-minecraft-clone\\res\\shaders\\basic\\vertex.glsl",
        "D:\\Programming\\Projects\\opengl-minecraft-clone\\res\\shaders\\basic\\fragment.glsl",

        camera
    );
    plane->add_position(glm::vec3(0.0f, 0.0f, -2.0f));
    plane->add_position(glm::vec3(0.0f, 0.0f, 3.0f));
    plane->add_position(glm::vec3(0.0f, 10.0f, 3.0f));
    plane->add_position(glm::vec3(-4.0f, -5.0f, 0.0f));
    plane->add_position(glm::vec3(10.0f, 5.0f, 7.0f));

    this->renderer.add(plane);
}

Application::~Application()
{
    delete this->camera;
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
    double this_frame_time = 0;
    double prev_frame_time = 0;

    while (!glfwWindowShouldClose(this->window->get_id()))
    {
        this_frame_time = glfwGetTime();
        this->delta_time = this_frame_time - prev_frame_time;

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        this->handle_input();
        this->renderer.submit();

        glfwSwapBuffers(this->window->get_id());
        glfwPollEvents();

        prev_frame_time = this_frame_time;
    }
}

void Application::handle_input()
{
    if (glfwGetKey(this->window->get_id(), GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(this->window->get_id(), GL_TRUE);

    if (glfwGetKey(this->window->get_id(), GLFW_KEY_W) == GLFW_PRESS)
        this->camera->move(Camera::Direction::forward, this->delta_time);
    else if (glfwGetKey(this->window->get_id(), GLFW_KEY_S) == GLFW_PRESS)
        this->camera->move(Camera::Direction::backward, this->delta_time);
    if (glfwGetKey(this->window->get_id(), GLFW_KEY_A) == GLFW_PRESS)
        this->camera->move(Camera::Direction::left, this->delta_time);
    else if (glfwGetKey(this->window->get_id(), GLFW_KEY_D) == GLFW_PRESS)
        this->camera->move(Camera::Direction::right, this->delta_time);
    if (glfwGetKey(this->window->get_id(), GLFW_KEY_SPACE) == GLFW_PRESS)
        this->camera->move(Camera::Direction::up, this->delta_time);
    else if (glfwGetKey(this->window->get_id(), GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
        this->camera->move(Camera::Direction::down, this->delta_time);
}

void Application::quit(int code)
{
    glfwTerminate();
    exit(code);
}