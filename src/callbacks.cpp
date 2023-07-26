#include "callbacks.hpp"
#include "Camera/Camera.hpp"
#include "Application/Application.hpp"

#include <iostream>

void cursor_pos_callback(GLFWwindow* window, double x, double y)
{
    Application* application = (Application*) glfwGetWindowUserPointer(window);
    Camera* camera = application->get_camera();

    if (camera->first_mouse_input)
    {
        camera->cursor_last_x = x;
        camera->cursor_last_y = y;
        camera->first_mouse_input = false;
    }

    camera->yaw += ((x - camera->cursor_last_x) * camera->sensitivity);
    camera->pitch += ((camera->cursor_last_y - y) * camera->sensitivity);

    camera->cursor_last_x = x;
    camera->cursor_last_y = y;

    // limit yaw and pitch
    if (camera->pitch > 89.0f)
        camera->pitch = 89.0f;
    else if (camera->pitch < -89.0f)
        camera->pitch = -89.0f;

    if (camera->yaw > 360.0f)
        camera->yaw = 0.0f;
    else if (camera->yaw < 0)
        camera->yaw = 360.0f;

    glm::vec3 direction {
        cos(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch)),
        sin(glm::radians(camera->pitch)),
        sin(glm::radians(camera->yaw)) * cos(glm::radians(camera->pitch))
    };
    camera->set_front(glm::normalize(direction));
    camera->update();
}

void keyboard_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    Application* application = (Application*) glfwGetWindowUserPointer(window);

    if (key == GLFW_KEY_F3 && action == GLFW_PRESS)
        application->toggle_debug_window();
}
