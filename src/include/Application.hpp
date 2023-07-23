#pragma once
#include "Window.hpp"

class Application
{
public:
    Application();
    ~Application();
    void start_loop();

private:
    void initialize_glew();
    void load_resources();

    Window window;
};