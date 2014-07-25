#include "bufferman.h"
#include "buffer.h"

const int POSITION_IDX = 0;
const int COLOR_IDX    = 1;
const int NORMAL_IDX   = 2;

BufferMan::BufferMan()
{
    glewInit();

    index_buffer_size = 0;
    vertex_buffer_size = 0;
    num_vertices = 0;
    is_setup = false;
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
    if(!is_setup) {
        for(Mesh *s : shapes) {
            s->store();
            index_buffer_size += s->getIndexBufferSize();
            vertex_buffer_size += s->getVertexBufferSize();
            num_vertices += s->getNumVertices();
        }
    } else {
        // calling this function past the 1st time will readd the data
        // to the graphics card
        delete vertex_buffer;
        delete index_buffer;
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
        if (s->hasColor()) {
            // add colors:
            offset = vertex_buffer->addData(
                        s->getColorAddress(),
                        s->getVertexBufferSubSize());
            s->setColorBufferOffset(offset);
        }
        // add indices:
        offset = index_buffer->addData(
                    s->getIndexAddress(),
                    s->getIndexBufferSize());
        s->setIndexBufferOffset(offset);

        if(is_setup) s->deleteVao();
        s->setVao(setupVAO(s));
    }

    if(!is_setup) is_setup = true;
}

GLuint BufferMan::setupVAO(Mesh *s)
{
    GLuint vao;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glEnableVertexAttribArray(POSITION_IDX);
    glVertexAttribPointer(POSITION_IDX, 3, GL_FLOAT, GL_FALSE, 0, (void*)s->getVertexBufferOffset());
    glEnableVertexAttribArray(NORMAL_IDX);
    glVertexAttribPointer(NORMAL_IDX, 3, GL_FLOAT, GL_FALSE, 0, (void*)s->getNormalBufferOffset());

    if (s->hasColor()) {
        glEnableVertexAttribArray(COLOR_IDX);
        glVertexAttribPointer(COLOR_IDX, 3, GL_FLOAT, GL_FALSE, 0, (void*)s->getColorBufferOffset());
    }

    glBindBuffer(vertex_buffer->getType(), vertex_buffer->getID());
    glBindBuffer(index_buffer->getType(), index_buffer->getID());

    return vao;
}
