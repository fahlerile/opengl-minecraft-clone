#include <vector>
#include <stdexcept>
#include <utility>

#define GLEW_STATIC
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Texture/Texture.hpp"
#include "Shader/Shader.hpp"
#include "Camera/Camera.hpp"
#include "utils/constants.hpp"
#include "Chunk.hpp"

// `textures` order is {back, front, left, right, top, bottom}
// `position` => {x, z} ONLY INTEGER VALUES!!!
Chunk::Chunk(glm::vec2 position) : model(
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
        2, 1, 0,
        2, 3, 1,

        4, 5, 6,
        5, 7, 6,

        8, 9, 10,
        9, 11, 10,

        12, 14, 13,
        13, 14, 15,

        16, 17, 18,
        17, 19, 18,

        22, 21, 20,
        22, 23, 21,
    }
)
{
    this->position = position * (float) CHUNK_SIZE;
}

// `position` is relative to this chunk
void Chunk::add_block(glm::vec3 block_position, std::vector<Texture*> textures)
{
    if ((block_position[0] < 0 && block_position[0] >= CHUNK_SIZE) || (block_position[2] < 0 && block_position[2] >= CHUNK_SIZE))
        throw std::invalid_argument("block position in chunk is more/less than chunk size/0");
    
    blocks.push_back(
        std::pair<glm::vec3, std::vector<Texture*>> {
            glm::vec3(this->position[0] + block_position[0], block_position[1], this->position[1] + block_position[2]),
            textures
        }
    );
}

// `position` is relative to this chunk
void Chunk::add_block(glm::vec3 block_position, Texture* texture)
{
    if ((block_position[0] < 0 && block_position[0] >= CHUNK_SIZE) || (block_position[2] < 0 && block_position[2] >= CHUNK_SIZE))
        throw std::invalid_argument("block position in chunk is more/less than chunk size/0");

    blocks.push_back(
        std::pair<glm::vec3, std::vector<Texture*>> {
            glm::vec3(this->position[0] + block_position[0], block_position[1], this->position[1] + block_position[2]),
            {texture, texture, texture, texture, texture, texture}
        }
    );
}

void Chunk::render(Shader* shader, Camera* camera)
{
    shader->use();
    glUniform1i(shader->get_uniform_location("texture_sampler"), 0);
    this->model.bindVAO();

    glm::mat4 view = camera->get_view_matrix();
    glUniformMatrix4fv(shader->get_uniform_location("view"), 1, GL_FALSE, glm::value_ptr(view));
    glm::mat4 projection = camera->get_projection_matrix();
    glUniformMatrix4fv(shader->get_uniform_location("projection"), 1, GL_FALSE, glm::value_ptr(projection));

    for (auto block : this->blocks)
    {
        glm::vec3 position = block.first;
        std::vector<Texture*> textures = block.second;

        glm::mat4 model(1.0f);
        model = glm::translate(model, position);
        glUniformMatrix4fv(shader->get_uniform_location("model"), 1, GL_FALSE, glm::value_ptr(model));

        for (int i = 0; i < 6; i++)
        {
            textures[i]->bind(0);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*) (i * 6 * sizeof(unsigned int)));
        }
    }
}
