#include "texture.h"
#include "shaderman.h"
#include <SFML/Graphics.hpp>
#include <iostream>

GLint Texture::texture_sampler_loc;

Texture::Texture(const std::string &path)
{
    glewInit();

    sf::Image img_data;
    if (!img_data.loadFromFile(path)) {
        std::cerr << "Could not load " << path << "\n";
        return;
    }

    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA,
                 img_data.getSize().x,
                 img_data.getSize().y,
                 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data.getPixelsPtr());
}

Texture::~Texture()
{
    glDeleteTextures(1, &textureID);
}

void Texture::setTextureSamplerLoc(const GLint &val)
{
    texture_sampler_loc = val;
}


void Texture::use()
{
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    glUniform1i(texture_sampler_loc, 0);
}

