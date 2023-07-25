#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.hpp"

Camera::Camera(glm::vec3 position, float fov, float speed, Window* window)
{
    this->position = position;
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->fov = fov;
    this->speed = speed;
    this->window = window;
    this->update();
}

void Camera::update()
{
    this->view = glm::lookAt(this->position, this->position + this->front, glm::vec3(0.0f, 1.0f, 0.0f));

    int width, height;
    glfwGetWindowSize(window->get_id(), &width, &height);

    this->projection = glm::perspective(this->fov, (float) width / height, 0.1f, 100.0f);
}

glm::mat4 Camera::get_view_matrix()
{
    return this->view;
}

glm::mat4 Camera::get_projection_matrix()
{
    return this->projection;
}

void Camera::move(Direction direction, double delta_time)
{
    float speed_this_frame = this->speed * delta_time;

    switch (direction)
    {
        case forward:
            this->position += (speed_this_frame * this->front);
            this->update();
            break;
        case backward:
            this->position -= (speed_this_frame * this->front);
            this->update();
            break;
        case left:
            this->position -= (speed_this_frame * glm::normalize(glm::cross(this->front, this->up)));
            this->update();
            break;
        case right:
            this->position += (speed_this_frame * glm::normalize(glm::cross(this->front, this->up)));
            this->update();
            break;
    }
}
