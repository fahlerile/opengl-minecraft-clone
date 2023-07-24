#pragma once

#include <string>

enum ShaderType {vertex, fragment};

class Shader
{
    private:
        unsigned int process_shader(std::string path, ShaderType type);
        unsigned int id;
    public:
        Shader(std::string vertex_path, std::string fragment_path);
        void use();
        void delete_shader();
        unsigned int get_uniform_location(const char *name);
};
