#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glew.h>
#include <string>

class ShaderMan;

class Texture
{
public:
    Texture(const std::string &path);
    virtual ~Texture();
    void use();

    static void setTextureSamplerLoc(const GLint &val);

private:
    GLuint textureID;
    static GLint texture_sampler_loc;
};

#endif // TEXTURE_H
