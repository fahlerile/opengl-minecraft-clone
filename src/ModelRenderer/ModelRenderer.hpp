#pragma once
#include <glm/glm.hpp>
#include "Model/Model.hpp"
#include "Shader/Shader.hpp"
#include "Camera/Camera.hpp"

class ModelRenderer
{
public:
    ModelRenderer(const std::vector<float>& data,
                  const std::vector<unsigned int>& indices,
                  std::string vertex_path,
                  std::string fragment_path,
                  Camera* camera);
    void add_position(glm::vec3 position);
    void render();

private:
    std::vector<glm::vec3> positions;
    Model model;
    Shader shader;
    Camera* camera;
};