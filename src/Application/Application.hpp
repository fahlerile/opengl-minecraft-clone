#pragma once
#include "Window/Window.hpp"
#include "BlockRenderer/BlockRenderer.hpp"
#include "Shader/Shader.hpp"

class Application
{
public:
    Application(Window* window);
    ~Application();
    void start_loop();
    void toggle_debug_window();
    Camera* get_camera();

private:
    void initialize_glew();
    void initialize_imgui();
    void load_resources();
    void handle_input();
    void quit(int code);

    Window* window;
    BlockRenderer* renderer;
    Shader* basic_shader;
    Camera* camera;
    double delta_time;
    bool show_debug_window = false;
};