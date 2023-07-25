#pragma once
#include <glm/glm.hpp>
#include "Window/Window.hpp"

class Camera
{
public:
    Camera(glm::vec3 position, glm::vec3 target, float fov, Window* window);
    void update();
    glm::mat4 get_view_matrix();
    glm::mat4 get_projection_matrix();
private:
    glm::vec3 position;
    glm::vec3 target;
    glm::mat4 view;
    glm::mat4 projection;
    float fov;
    Window* window;
};