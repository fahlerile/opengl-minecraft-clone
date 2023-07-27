#pragma once
#include <vector>
#include <utility>

#include "Texture/Texture.hpp"
#include "Shader/Shader.hpp"
#include "Camera/Camera.hpp"
#include "Model/Model.hpp"

class BlockRenderer
{
public:
    BlockRenderer(Shader* shader,
                  Camera* camera);
    void add_block(glm::vec3 position, std::vector<Texture*> textures);
    void render();

private:
    std::vector<std::pair<glm::vec3, std::vector<Texture*>>> blocks;
    Model model;
    Shader* shader;
    Camera* camera;
};