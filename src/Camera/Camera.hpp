#pragma once
#include <glm/glm.hpp>
#include "Window/Window.hpp"

class Camera
{
public:
    enum Direction {forward, backward, left, right};

    Camera(glm::vec3 position, float fov, float speed, Window* window);
    void update();
    void move(Direction direction, double delta_time);
    glm::mat4 get_view_matrix();
    glm::mat4 get_projection_matrix();
private:
    glm::vec3 position;
    glm::vec3 front;
    static constexpr glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);
    glm::mat4 view;
    glm::mat4 projection;
    float fov;
    float speed;
    Window* window;
};