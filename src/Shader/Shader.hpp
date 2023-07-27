#pragma once

#include <string>

enum ShaderType {vertex, fragment};

class Shader
{
    public:
        Shader(std::string vertex_path, std::string fragment_path);
        ~Shader();
        void use();
        unsigned int get_uniform_location(const char *name);
    private:
        unsigned int process_shader(std::string path, ShaderType type);
        unsigned int id;
};
