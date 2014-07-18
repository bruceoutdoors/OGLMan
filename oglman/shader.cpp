#include "shader.h"
#include <fstream>
#include <iostream>
#include <cassert>

Shader::Shader(GLenum type)
{
    glewInit();

    SHADER_TYPE = type;
    shaderID = glCreateShader(SHADER_TYPE);
}

Shader::~Shader()
{
    glDeleteShader(shaderID);
}

bool Shader::loadFile(std::string path)
{
    std::ifstream inFile(path.c_str());

    if (!inFile.is_open()) {
        std::cerr << "Failed to open file: " << path << std::endl;
        return false;
    }

    std::string source_code = std::string(
                std::istreambuf_iterator<char>(inFile),
                std::istreambuf_iterator<char>());

    inFile.close();

    filepath = std::string(path);
    source = source_code;

    return true;
}

void Shader::compile()
{
    const char *shader_source[] = { source.c_str() };
    glShaderSource(shaderID, 1, shader_source, 0);
    glCompileShader(shaderID);

    // shader error checking
    assert(checkShader());
}

GLuint Shader::getID() const
{
    return shaderID;
}

bool Shader::checkShader()
{
    GLint isSuccess = GL_FALSE;
    glGetShaderiv(shaderID, GL_COMPILE_STATUS, &isSuccess);
    if (isSuccess == GL_FALSE) {
        GLint maxLength;
        glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &maxLength);

        GLchar *infoLog = new GLchar[maxLength];
        glGetShaderInfoLog(shaderID, maxLength, NULL, infoLog);

        std::cerr << "Shader compile error for " << filepath << " -> " << infoLog << std::endl;
        delete[] infoLog;

        return false;
    }
    return true;
}
