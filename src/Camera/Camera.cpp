#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "Camera.hpp"

Camera::Camera(glm::vec3 position, glm::vec3 target, float fov, Window* window)
{
    this->position = position;
    this->target = target;
    this->fov = fov;
    this->window = window;
    this->update();
}

void Camera::update()
{
    this->view = glm::lookAt(this->position, this->target, glm::vec3(0.0f, 1.0f, 0.0f));

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
