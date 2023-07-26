#pragma once
#include <vector>
#include "ModelRenderer/ModelRenderer.hpp"

class Renderer
{
public:
    void add(ModelRenderer *model_renderer);
    void submit();
    void begin();
    void end(Window* window);
private:
    std::vector<ModelRenderer*> model_renderers;
};