#pragma once
#include <glm/glm.hpp>
#include "Model/Model.hpp"

class ModelRenderer
{
public:
    ModelRenderer(const std::vector<float> &data,
                  const std::vector<unsigned int> &indices);
    void add_position(glm::vec3 position);
    void render();

private:
    std::vector<glm::vec3> positions;
    Model model;
};