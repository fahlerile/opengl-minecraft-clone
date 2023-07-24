#include "Renderer.hpp"

void Renderer::add(ModelRenderer *model_renderer)
{
    this->model_renderers.push_back(model_renderer);
}

void Renderer::submit()
{
    for (auto model_renderer : this->model_renderers)
    {
        model_renderer->render();
    }
}