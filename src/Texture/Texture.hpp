#pragma once
#include <string>

class Texture
{
public:
    Texture(std::string path);
    ~Texture();
    void bind(unsigned int unit);
private:
    unsigned int id = 0;
};