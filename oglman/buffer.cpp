#include "buffer.h"

Buffer::Buffer(GLenum TYPE, GLuint size)
{
    glewInit();

    BUFFER_TYPE = TYPE;
    offset = 0;

    glGenBuffers(1, &bufferID);
    glBindBuffer(BUFFER_TYPE, bufferID);
    glBufferData(BUFFER_TYPE, size, 0, GL_STATIC_DRAW);
}

Buffer::~Buffer()
{
    glDeleteBuffers(1, &bufferID);
}

// adds the data and returns the buffer offset to it
GLuint Buffer::addData(const GLvoid *data, GLsizeiptr size)
{
    GLuint old_offset = offset;

    glBufferSubData(BUFFER_TYPE, offset, size, data);
    offset += size;

    return old_offset;
}

GLuint Buffer::getOffset() const
{
    return offset;
}

GLenum Buffer::getType() const
{
    return BUFFER_TYPE;
}

GLuint Buffer::getSize() const
{
    return size;
}

GLuint Buffer::getID() const
{
    return bufferID;
}
