#pragma once
#include <vector>
#include <utility>

#include "Shader/Shader.hpp"
#include "Camera/Camera.hpp"
#include "Chunk/Chunk.hpp"

class Renderer
{
public:
    Renderer(Shader* shader,
             Camera* camera);
    void add_chunk(Chunk* chunk);
    void render();
    void begin();
    void end(Window* window);

private:
    std::vector<Chunk*> chunks;
    Shader* shader;
    Camera* camera;
};