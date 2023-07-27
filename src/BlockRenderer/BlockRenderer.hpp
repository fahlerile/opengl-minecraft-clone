#pragma once
#include "Texture/Texture.hpp"
#include "Shader/Shader.hpp"
#include "Camera/Camera.hpp"
#include "Model/Model.hpp"

class BlockRenderer
{
public:
    BlockRenderer(Texture* texture,
                  Shader* shader,
                  Camera* camera);
    void add_position(glm::vec3 position);
    void render();

private:
    std::vector<glm::vec3> positions;
    Model model;
    Texture* texture;
    Shader* shader;
    Camera* camera;
};