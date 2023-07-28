#pragma once
#include <map>
#include <string>

#include "Window/Window.hpp"
#include "Camera/Camera.hpp"
#include "Renderer/Renderer.hpp"
#include "Shader/Shader.hpp"

class Application
{
public:
    Application(Window* window);
    ~Application();
    void start_loop();
    void toggle_debug_window();
    void toggle_wireframe_mode();
    Camera* get_camera();

private:
    void initialize_glew();
    void initialize_imgui();
    void load_resources();
    void handle_input();
    void quit(int code);

    Window* window;
    Renderer* renderer;
    Shader* basic_shader;
    Camera* camera;

    std::map<std::string, Texture*> textures;
    std::map<std::string, Shader*> shaders;

    double delta_time;
    bool show_debug_window = false;
    bool wireframe_mode = false;
};