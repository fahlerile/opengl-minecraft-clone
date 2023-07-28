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
    Chunk();

    void add_block(glm::vec3 position, std::vector<Texture*> textures);
    void add_block(glm::vec3 position, Texture* texture);
    void render(Shader* shader, Camera* camera);

private:
    std::vector<std::pair<glm::vec3, std::vector<Texture*>>> blocks;
    // std::map<glm::vec3, std::vector<Texture*>> blocks;
    Model model;
};