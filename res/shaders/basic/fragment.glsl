#version 330 core

// in vec2 texture_coords;

out vec4 FragColor;

// uniform sampler2D texture_sampler;

void main()
{
    // FragColor = texture(texture_sampler, texture_coords);
    FragColor = vec4(1.0f, 0.0f, 0.0f, 1.0f);
}