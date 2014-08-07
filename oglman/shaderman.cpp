#include "shaderman.h"
#include "shader.h"
#include "camera.h"

#include <cassert>
#include <iostream>

using std::string;
using glm::vec3;
using glm::vec4;

const int POSITION_IDX = 0;
const int COLOR_IDX    = 1;
const int NORMAL_IDX   = 2;
const int UV_IDX       = 3;

// delegating constructor (C++11)
ShaderMan::ShaderMan(string shader_path) :
    ShaderMan(shader_path + ".vert",
              shader_path + ".frag") {}

ShaderMan::ShaderMan(string vert_path, string frag_path)
{
    glewInit();

    programID = glCreateProgram();

    vertex_shader = new Shader(GL_VERTEX_SHADER);
    assert(vertex_shader->loadFile(vert_path));
    vertex_shader->compile();
    glAttachShader(programID, vertex_shader->getID());

    fragment_shader = new Shader(GL_FRAGMENT_SHADER);
    assert(fragment_shader->loadFile(frag_path));
    fragment_shader->compile();
    glAttachShader(programID, fragment_shader->getID());

    glBindAttribLocation(programID, POSITION_IDX, "vertexPositionModel");
    glBindAttribLocation(programID, COLOR_IDX, "vertexColor");
    glBindAttribLocation(programID, NORMAL_IDX, "normalModel");
    glBindAttribLocation(programID, UV_IDX, "vertexUV");

    glLinkProgram(programID);

    assert(checkProgram());

    glDetachShader(programID, vertex_shader->getID());
    glDetachShader(programID, fragment_shader->getID());

    delete fragment_shader;
    delete vertex_shader;
}

ShaderMan::~ShaderMan()
{
    glDeleteProgram(programID);
}

void ShaderMan::use()
{
    glUseProgram(programID);
}

GLint ShaderMan::getUniformLoc(std::string name)
{
    return glGetUniformLocation(programID, name.c_str());
}

bool ShaderMan::checkProgram()
{
    GLint isSuccess = GL_FALSE;
    glGetProgramiv(programID, GL_LINK_STATUS, &isSuccess);
    if (isSuccess == GL_FALSE) {
        GLint maxLength;
        glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &maxLength);
        //The maxLength includes the NULL character
        GLchar *infoLog = new GLchar[maxLength];
        glGetProgramInfoLog(programID, maxLength, NULL, infoLog);

        std::cerr << "Shader link error: " << infoLog;
        delete[] infoLog;

        return false;
    }
    return true;
}
