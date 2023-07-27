#pragma once
#include <vector>
#include "Texture/Texture.hpp"
#include "Shader/Shader.hpp"
#include "Camera/Camera.hpp"
#include "Model/Model.hpp"

class BlockRenderer
{
public:
    BlockRenderer(std::vector<Texture*> textures,
                  Shader* shader,
                  Camera* camera);
    void add_position(glm::vec3 position);
    void render();

private:
    std::vector<glm::vec3> positions;
    Model model;
    std::vector<Texture*> textures;
    Shader* shader;
    Camera* camera;
};