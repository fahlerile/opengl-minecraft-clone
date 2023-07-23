#version 330 core

layout (location = 0) in vec3 l_position;
layout (location = 1) in vec2 l_texture_coords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

out vec2 texture_coords;

void main()
{
    gl_Position = projection * view * model * vec4(l_position, 1.0);
    texture_coords = l_texture_coords;
}