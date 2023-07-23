#pragma once
#include <GLFW/glfw3.h>

class Window
{
public:
    Window(unsigned int height, unsigned int width, const char *title);
    GLFWwindow* get_id();

private:
    GLFWwindow* id;
};