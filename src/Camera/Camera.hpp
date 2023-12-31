#pragma once
#include <glm/glm.hpp>
#include "Window/Window.hpp"

class Camera
{
public:
    enum Direction {forward, backward, left, right, up, down};

    Camera(glm::vec3 position, float fov, float speed, Window* window);

    void update();
    void move(Direction direction, double delta_time);

    bool first_mouse_input = true;
    double cursor_last_x;
    double cursor_last_y;
    float sensitivity = 0.1f;
    double yaw = 0.0;
    double pitch = 0.0;

    glm::vec3 get_position();
    glm::mat4 get_view_matrix();
    glm::mat4 get_projection_matrix();

    void set_front(glm::vec3 new_front);

private:
    glm::vec3 position;
    glm::vec3 front;
    static constexpr glm::vec3 up_vec = glm::vec3(0.0f, 1.0f, 0.0f);

    glm::mat4 view;
    glm::mat4 projection;

    float fov;
    float speed;

    Window* window;
};