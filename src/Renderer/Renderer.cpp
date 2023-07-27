#include <imgui/imgui.h>
#include <imgui/imgui_impl_glfw.h>
#include <imgui/imgui_impl_opengl3.h>
#include "Renderer.hpp"
#include "Window/Window.hpp"

// Add a new model renderer to render
void Renderer::add(ModelRenderer *model_renderer)
{
    this->model_renderers.push_back(model_renderer);
}

// Submit model renderers for render
void Renderer::submit()
{
    for (auto model_renderer : this->model_renderers)
    {
        model_renderer->render();
    }
}

// Called before rendering a frame
void Renderer::begin()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

// Called after rendering a frame
void Renderer::end(Window* window)
{
    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    glfwSwapBuffers(window->get_id());
    glfwPollEvents();
}