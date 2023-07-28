#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>

#include "Renderer.hpp"
#include "Chunk/Chunk.hpp"
#include "Shader/Shader.hpp"
#include "Camera/Camera.hpp"

Renderer::Renderer(Shader* shader,
                   Camera* camera)
{
    this->shader = shader;
    this->camera = camera;
    this->chunks.clear();
}

void Renderer::add_chunk(Chunk* chunk)
{
    this->chunks.push_back(chunk);
}

void Renderer::render()
{
    for (auto chunk : this->chunks)
        chunk->render(this->shader, this->camera);
}

void Renderer::begin()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Renderer::end(Window* window)
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window->get_id());
    glfwPollEvents();
}

std::vector<Chunk*> Renderer::get_chunk_vector()
{
    return this->chunks;
}