#include "bufferman.h"
#include "buffer.h"

const int POSITION_IDX = 0;
const int NORMAL_IDX = 2;

BufferMan::BufferMan()
{
    glewInit();

    index_buffer_size = 0;
    vertex_buffer_size = 0;
    num_vertices = 0;
}

BufferMan::~BufferMan()
{
    delete vertex_buffer;
    delete index_buffer;
}

void BufferMan::addShape(Mesh *s)
{
    shapes.push_back(s);
}

GLuint BufferMan::getTotalVectices() const
{
    return num_vertices;
}

void BufferMan::setupBuffers()
{
    for(Mesh *s : shapes) {
        s->store();
        index_buffer_size += s->getIndexBufferSize();
        vertex_buffer_size += s->getVertexBufferSize();
    }

    vertex_buffer = new Buffer(GL_ARRAY_BUFFER, vertex_buffer_size);
    index_buffer = new Buffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size);

    GLuint offset;
    for(Mesh *s : shapes) {
        // add vertices:
        offset = vertex_buffer->addData(
                    s->getVertexAddress(),
                    s->getVertexBufferSubSize());
        s->setVertexBufferOffset(offset);
        // add normals:
        offset = vertex_buffer->addData(
                    s->getNormalAddress(),
                    s->getVertexBufferSubSize());
        s->setNormalBufferOffset(offset);
        // add indices:
        offset = index_buffer->addData(
                    s->getIndexAddress(),
                    s->getIndexBufferSize());
        s->setIndexBufferOffset(offset);

        num_vertices += s->getNumVertices();
        s->setVao(setupVAO(s));
    }
}

GLuint BufferMan::setupVAO(Mesh *s)
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(POSITION_IDX);
    glEnableVertexAttribArray(NORMAL_IDX);
    glBindBuffer(vertex_buffer->getType(), vertex_buffer->getID());
    glVertexAttribPointer(POSITION_IDX, 3, GL_FLOAT, GL_FALSE, 0, (void*)s->getVertexBufferOffset());
    glVertexAttribPointer(NORMAL_IDX, 3, GL_FLOAT, GL_FALSE, 0, (void*)s->getNormalBufferOffset());
    glBindBuffer(index_buffer->getType(), index_buffer->getID());

    return vao;
}
