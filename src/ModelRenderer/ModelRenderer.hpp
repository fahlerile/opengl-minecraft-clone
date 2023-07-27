#pragma once
#include <glm/glm.hpp>
#include "Model/Model.hpp"
#include "Shader/Shader.hpp"
#include "Camera/Camera.hpp"
#include "Texture/Texture.hpp"

class ModelRenderer
{
public:
    ModelRenderer(const std::vector<float>& data,
                  const std::vector<unsigned int>& indices,
                  Texture* texture,
                  Shader* shader,
                  Camera* camera);
    void add_position(glm::vec3 position);
    void render();

protected:
    std::vector<glm::vec3> positions;
    Model model;
    Texture* texture;
    Shader* shader;
    Camera* camera;
};