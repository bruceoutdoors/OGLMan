#ifndef BUFFERMAN_H
#define BUFFERMAN_H

#include <GL/glew.h>
#include <vector>

#include "mesh.h"

class Buffer; //forward class

class BufferMan
{
public:
    BufferMan();
    ~BufferMan();
    void draw();
    void addShape(Mesh *s);
    GLuint getTotalVectices() const;
    void setupBuffers();

private:
    GLuint setupVAO(Mesh *s);

    GLuint index_buffer_size;
    GLuint array_buffer_size;
    GLuint num_vertices;
    std::vector<Mesh*> shapes;
    Buffer *array_buffer;
    Buffer *index_buffer;

    bool is_setup;
};

#endif // BUFFERMAN_H
