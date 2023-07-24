#define GLEW_STATIC
#include <GL/glew.h>
#include "ModelRenderer.hpp"

#include <iostream>
#include <cstdlib>

ModelRenderer::ModelRenderer(const std::vector<float>& data,
                             const std::vector<unsigned int>& indices) :
                             model(data, indices)
{}

void ModelRenderer::add_position(glm::vec3 position)
{
    this->positions.push_back(position);
}

void ModelRenderer::render()
{
    this->model.bindVAO();

    // TODO: add translation matrix for `position`
    for (auto position : this->positions)
    {
        glDrawElements(GL_TRIANGLES, this->model.get_indices_count(), GL_UNSIGNED_INT, nullptr);
    }
}