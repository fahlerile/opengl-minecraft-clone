#pragma once
#include "ModelRenderer/ModelRenderer.hpp"
#include "Model/Model.hpp"

class BlockRenderer : public ModelRenderer
{
public:
    BlockRenderer(Texture* texture,
                  Shader* shader,
                  Camera* camera);
    
private:
};