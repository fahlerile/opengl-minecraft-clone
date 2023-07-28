#include <iostream>
#include <cstdlib>
#include <filesystem>
#include <sstream>

#define GLEW_STATIC
#include <GL/glew.h>

#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include <glm/gtx/string_cast.hpp>

#include "Application.hpp"
#include "Window/Window.hpp"
#include "Shader/Shader.hpp"
#include "Texture/Texture.hpp"
#include "Renderer/Renderer.hpp"
#include "utils/callbacks.hpp"
#include "utils/constants.hpp"

Application::Application(Window* window)
{
    this->window = window;
    this->camera = new Camera(glm::vec3(0.0f, 0.0f, 0.0f), 45.0f, 5.0f, this->window);

    this->initialize_glew();
    this->initialize_imgui();
    this->load_resources();

    this->renderer = new Renderer(this->shaders["basic"], this->camera);

    glfwSetInputMode(this->window->get_id(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetWindowUserPointer(this->window->get_id(), this);
    glfwSetKeyCallback(this->window->get_id(), keyboard_callback);
    glfwSetCursorPosCallback(this->window->get_id(), cursor_pos_callback);

    Chunk* p_chunk;
    p_chunk = new Chunk(glm::vec2(0, 0));
    for (int x = 0; x < 16; x++)
        for (int z = 0; z < 16; z++)
            p_chunk->add_block(glm::vec3(x, 0, z), this->textures["dirt"]);
    this->renderer->add_chunk(p_chunk);

    p_chunk = new Chunk(glm::vec2(1, 0));
    for (int x = 0; x < 16; x++)
        for (int z = 0; z < 16; z++)
            p_chunk->add_block(glm::vec3(x, 0, z), this->textures["stone"]);
    this->renderer->add_chunk(p_chunk);
}

// Delete heap allocated resources here, uninitialize libraries
Application::~Application()
{
    // free heap allocated resources
    for (auto p_chunk : this->renderer->get_chunk_vector())
        delete p_chunk;

    delete this->camera;
    delete this->renderer;

    for (auto item : this->textures)
        delete item.second;
    for (auto item : this->shaders)
        delete item.second;

    // deinit libraries
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    glfwTerminate();
}

// Initialize GLEW library (OpenGL)
void Application::initialize_glew()
{
    if (glewInit())
    {
        std::cout << "Failed to initialize GLEW" << std::endl;
        this->quit(2);
    }
    glEnable(GL_DEPTH_TEST);  // enable Z-buffer
}

// Initialize imgui library
void Application::initialize_imgui()
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO(); (void) io;
    ImGui::StyleColorsDark();
    ImGui_ImplGlfw_InitForOpenGL(this->window->get_id(), true);
    ImGui_ImplOpenGL3_Init("#version 330");

    // force not to use imgui.ini
    io.IniFilename = nullptr;
    io.LogFilename = nullptr;
}

// Load necessary resources (e.g textures, sounds, shaders)
void Application::load_resources()
{
    std::filesystem::path textures_path(TEXTURES_PATH);
    for (auto entry : std::filesystem::directory_iterator(textures_path))
    {
        std::filesystem::path path = entry.path();
        std::string filename = path.filename().string();
        filename = filename.substr(0, filename.find('.'));

        this->textures[filename] = new Texture(path.string());
    }

    std::filesystem::path shaders_path(SHADERS_PATH);
    for (auto entry : std::filesystem::directory_iterator(shaders_path))
    {
        std::filesystem::path path = entry.path();
        std::string filename = path.filename().string();

        this->shaders[filename] = new Shader((path / "vertex.glsl").string(),
                                             (path / "fragment.glsl").string());
    }
}

// Starts a main application loop
void Application::start_loop()
{
    double this_frame_time = 0;
    double prev_frame_time = 0;

    while (!glfwWindowShouldClose(this->window->get_id()))
    {
        this_frame_time = glfwGetTime();
        this->delta_time = this_frame_time - prev_frame_time;

        this->renderer->begin();

        this->handle_input();
        this->renderer->render();

        if (this->show_debug_window)
        {
            ImGui::Begin("Debug", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoScrollbar | ImGuiWindowFlags_NoSavedSettings | ImGuiWindowFlags_NoInputs);
            std::stringstream debug_ss;
            debug_ss << "FPS: " << 1 / this->delta_time << "\n"
                     << "Frametime: " << this->delta_time * 1000 << "ms\n"
                     << "Position: " << glm::to_string(this->camera->get_position()) << "\n";
            ImGui::Text(debug_ss.str().c_str());  // in-built formatting does not work, so using sstream
            ImGui::End();
        }

        this->renderer->end(this->window);

        prev_frame_time = this_frame_time;
    }
}

// Handle user input (for toggling some states (e.g debug window state) use callbacks.cpp:keyboard_callback)
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

// Toggle visibility of a debug window
void Application::toggle_debug_window()
{
    this->show_debug_window = !(this->show_debug_window);
}

// Toggle wireframe mode. Yes.
void Application::toggle_wireframe_mode()
{
    if (this->wireframe_mode)
    {
        this->wireframe_mode = false;
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }
    else
    {
        this->wireframe_mode = true;
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    }
}

// Get a pointer to camera object
Camera* Application::get_camera()
{
    return this->camera;
}

// Quit from application
void Application::quit(int code)
{
    glfwTerminate();
    exit(code);
}