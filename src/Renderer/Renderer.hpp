#pragma once
#include <vector>
#include "ModelRenderer/ModelRenderer.hpp"

class Renderer
{
public:
    void add(ModelRenderer *model_renderer);
    void submit();
private:
    std::vector<ModelRenderer*> model_renderers;
};