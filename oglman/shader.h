#ifndef SHADER_H
#define SHADER_H

#include <GL/glew.h>
#include <string>

class Shader
{
public:
    Shader(GLenum type);
    virtual ~Shader();
    bool loadFile(std::string path);
    void compile();
    GLuint getID() const;

private:
    bool checkShader();

    GLenum SHADER_TYPE;
    GLuint shaderID;
    std::string filepath;
    std::string source;


};

#endif // SHADER_H
