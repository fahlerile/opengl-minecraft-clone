#include <string>

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ModelRenderer.hpp"
#include "Texture/Texture.hpp"
#include "Shader/Shader.hpp"
#include "Camera/Camera.hpp"

ModelRenderer::ModelRenderer(const std::vector<float>& data,
                             const std::vector<unsigned int>& indices,
                             Texture* texture,
                             Shader* shader,
                             Camera* camera) :
                             model(data, indices)
{
    this->texture = texture;
    this->shader = shader;
    this->camera = camera;
}

void ModelRenderer::add_position(glm::vec3 position)
{
    this->positions.push_back(position);
}

void ModelRenderer::render()
{
    this->shader->use();
    glUniform1i(this->shader->get_uniform_location("texture_sampler"), 0);
    this->texture->bind(0);
    this->model.bindVAO();

    glm::mat4 view = this->camera->get_view_matrix();
    glUniformMatrix4fv(this->shader->get_uniform_location("view"), 1, GL_FALSE, glm::value_ptr(view));
    glm::mat4 projection = this->camera->get_projection_matrix();
    glUniformMatrix4fv(this->shader->get_uniform_location("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    for (auto position : this->positions)
    {
        glm::mat4 model(1.0f);
        model = glm::translate(model, position);
        glUniformMatrix4fv(this->shader->get_uniform_location("model"), 1, GL_FALSE, glm::value_ptr(model));

        glDrawElements(GL_TRIANGLES, this->model.get_indices_count(), GL_UNSIGNED_INT, nullptr);
    }
}