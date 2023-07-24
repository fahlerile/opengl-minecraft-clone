#pragma once
#include <vector>

class Model
{
public:
    Model(const std::vector<float> &data,
          const std::vector<unsigned int> &indices);
    ~Model();

    void bindVAO();
    unsigned int get_indices_count();

private:
    void addEBO(std::vector<unsigned int> data);

    unsigned int VAO = 0;
    unsigned int indices_count = 0;
    unsigned int vbo_count = 0;

    std::vector<unsigned int> buffers;
};