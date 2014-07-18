#ifndef BUFFER_H
#define BUFFER_H

#include <GL/glew.h>
#include <vector>

class Buffer
{
public:
    Buffer(GLenum TYPE, GLuint size);
    virtual ~Buffer();
    GLuint addData(const GLvoid *data, GLsizeiptr size);
    GLuint getOffset() const;
    GLenum getType() const;
    GLuint getSize() const;
    GLuint getID() const;

private:
    GLuint offset;
    GLuint bufferID;
    GLuint size;
    GLenum BUFFER_TYPE;
};

#endif // BUFFER_H
