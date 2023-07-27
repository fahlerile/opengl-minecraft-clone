#include <vector>

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture/Texture.hpp"
#include "Shader/Shader.hpp"
#include "Camera/Camera.hpp"
#include "BlockRenderer.hpp"

// `textures` order is {back, front, left, right, top, bottom}
BlockRenderer::BlockRenderer(std::vector<Texture*> textures,
                             Shader* shader,
                             Camera* camera) :
                             model(
                                {
                                    // back side
                                    1.0f, 1.0f, 0.0f,   1.0f, 1.0f,
                                    0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
                                    1.0f, 0.0f, 0.0f,   1.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f,   0.0f, 0.0f,

                                    // front side
                                    1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
                                    0.0f, 1.0f, 1.0f,   0.0f, 1.0f,
                                    1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f,   0.0f, 0.0f,

                                    // left side
                                    0.0f, 1.0f, 1.0f,   1.0f, 1.0f,
                                    0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
                                    0.0f, 0.0f, 1.0f,   1.0f, 0.0f,
                                    0.0f, 0.0f, 0.0f,   0.0f, 0.0f,

                                    // right side
                                    1.0f, 1.0f, 1.0f,   1.0f, 1.0f,
                                    1.0f, 1.0f, 0.0f,   0.0f, 1.0f,
                                    1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
                                    1.0f, 0.0f, 0.0f,   0.0f, 0.0f,

                                    // top side
                                    1.0f, 1.0f, 0.0f,   1.0f, 1.0f,
                                    0.0f, 1.0f, 0.0f,   0.0f, 1.0f,
                                    1.0f, 1.0f, 1.0f,   1.0f, 0.0f,
                                    0.0f, 1.0f, 1.0f,   0.0f, 0.0f,

                                    // bottom side
                                    1.0f, 0.0f, 0.0f,   1.0f, 1.0f,
                                    0.0f, 0.0f, 0.0f,   0.0f, 1.0f,
                                    1.0f, 0.0f, 1.0f,   1.0f, 0.0f,
                                    0.0f, 0.0f, 1.0f,   0.0f, 0.0f
                                },
                                {
                                    0, 1, 2,
                                    1, 2, 3,

                                    4, 5, 6,
                                    5, 6, 7,

                                    8, 9, 10,
                                    9, 10, 11,

                                    12, 13, 14,
                                    13, 14, 15,

                                    16, 17, 18,
                                    17, 18, 19,

                                    20, 21, 22,
                                    21, 22, 23
                                }
                             )
{
    this->textures = textures;
    this->shader = shader;
    this->camera = camera;
}

void BlockRenderer::add_position(glm::vec3 position)
{
    this->positions.push_back(position);
}

void BlockRenderer::render()
{
    this->shader->use();
    glUniform1i(this->shader->get_uniform_location("texture_sampler"), 0);
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

        for (int i = 0; i < 6; i++)
        {
            this->textures[i]->bind(0);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) (i * 6 * sizeof(unsigned int)));
        }

    }
}
