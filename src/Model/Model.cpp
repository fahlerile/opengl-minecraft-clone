#define GLEW_STATIC
#include <GL/glew.h>
#include "Model.hpp"

// assumes that data consists of 5 floats per vertex (3 - positions, 2 - texture coords)
Model::Model(const std::vector<float> &data,
             const std::vector<unsigned int> &indices)
{
    this->indices_count = indices.size();

    glGenVertexArrays(1, &(this->VAO));
    this->bindVAO();

    unsigned int VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) 0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*) (3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    this->buffers.push_back(VBO);

    addEBO(indices);
}

Model::~Model()
{
    glDeleteVertexArrays(1, &(this->VAO));
    glDeleteBuffers(this->buffers.size(), this->buffers.data());
    this->buffers.clear();
    this->VAO = 0;
    this->vbo_count = 0;
    this->indices_count = 0;
}

void Model::bindVAO()
{
    glBindVertexArray(this->VAO);
}

void Model::addEBO(std::vector<unsigned int> data)
{
    unsigned int EBO;
    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, data.size() * sizeof(unsigned int), data.data(), GL_STATIC_DRAW);

    this->buffers.push_back(EBO);
}

unsigned int Model::get_indices_count()
{
    return this->indices_count;
}