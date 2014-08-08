#ifndef BUFFERMAN_H
#define BUFFERMAN_H

#include <GL/glew.h>
#include <vector>

class Buffer; //forward class
class Mesh;

class BufferMan
{
public:
    BufferMan();
    ~BufferMan();
    void draw(bool isWireframe = false);
    void drawSelected();
    void deselectAll();
    void addShape(Mesh *s);
    GLuint getTotalVectices() const;
    void setupBuffers();

    typedef std::vector<Mesh*>::iterator It;
    It getMeshesBegin();
    It getMeshesEnd();

private:
    GLuint setupVAO(Mesh *s);

    GLuint index_buffer_size;
    GLuint array_buffer_size;
    GLuint num_vertices;
    std::vector<Mesh*> meshes;
    Buffer *array_buffer;
    Buffer *index_buffer;

    bool is_setup;
};

#endif // BUFFERMAN_H
