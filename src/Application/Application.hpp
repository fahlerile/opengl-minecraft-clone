#pragma once
#include "Window/Window.hpp"
#include "Renderer/Renderer.hpp"
#include "Shader/Shader.hpp"

class Application
{
public:
    Application(Window* window);
    ~Application();
    void start_loop();

private:
    void initialize_glew();
    void load_resources();
    void quit(int code);

    Window* window;
    Renderer renderer;
    Shader* basic_shader;
    Camera* camera;
};