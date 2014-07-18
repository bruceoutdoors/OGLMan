#ifndef SHADERMAN_H
#define SHADERMAN_H

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>

using std::string;
using glm::vec4;
using glm::vec3;

// forward class
class Shader;
class Camera;

class ShaderMan
{
public:
    ShaderMan(std::string shader_path);
    ShaderMan(string vert_path, string frag_path);
    virtual ~ShaderMan();

    GLint getUniformLoc(std::string name);
    void use();

private:
    bool checkProgram();

    GLuint programID;
    Shader *vertex_shader;
    Shader *fragment_shader;

    // unusable copy constructors
    ShaderMan(ShaderMan const&);
    void operator=(ShaderMan const&);
};

#endif // SHADERMAN_H
