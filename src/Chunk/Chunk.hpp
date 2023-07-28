#pragma once
#include <vector>
#include <utility>

#include "Texture/Texture.hpp"
#include "Shader/Shader.hpp"
#include "Camera/Camera.hpp"
#include "Model/Model.hpp"

class Chunk
{
public:
    Chunk(glm::vec2 position);

    void add_block(glm::vec3 block_position, std::vector<Texture*> textures);
    void add_block(glm::vec3 block_position, Texture* texture);
    void render(Shader* shader, Camera* camera);

private:
    std::vector<std::pair<glm::vec3, std::vector<Texture*>>> blocks;
    // std::map<glm::vec3, std::vector<Texture*>> blocks;
    Model model;
    glm::vec2 position;  // the beginning of this chunk IN WORLD COORDINATES!
};