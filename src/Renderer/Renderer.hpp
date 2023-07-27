#pragma once
#include <vector>
#include "BlockRenderer/BlockRenderer.hpp"

class Renderer
{
public:
    void add(BlockRenderer *model_renderer);
    void submit();
    void begin();
    void end(Window* window);
private:
    std::vector<BlockRenderer*> model_renderers;
};