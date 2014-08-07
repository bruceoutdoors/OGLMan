#include "bufferman.h"
#include "buffer.h"

const int POSITION_IDX = 0;
const int COLOR_IDX    = 1;
const int NORMAL_IDX   = 2;
const int UV_IDX       = 3;

BufferMan::BufferMan()
{
    glewInit();

    index_buffer_size = 0;
    array_buffer_size = 0;
    num_vertices = 0;
    is_setup = false;
}

BufferMan::~BufferMan()
{
    for (Mesh *s : shapes) delete s;

    delete array_buffer;
    delete index_buffer;
}

void BufferMan::draw()
{
    for (Mesh *s : shapes) s->draw();
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
            array_buffer_size += s->getArrayBufferSize();
            num_vertices += s->getNumVertices();
        }
    } else {
        // calling this function past the 1st time will readd the data
        // to the graphics card
        delete array_buffer;
        delete index_buffer;
    }

    array_buffer = new Buffer(GL_ARRAY_BUFFER, array_buffer_size);
    index_buffer = new Buffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer_size);

    GLuint offset;
    for(Mesh *s : shapes) {
        if (s->isInstance()) {
            s->setupInstance();
        } else {
            // add vertices:
            offset = array_buffer->addData(
                        s->getVertexAddress(),
                        s->getVertexBufferSize());
            s->setVertexBufferOffset(offset);
            // add normals:
            offset = array_buffer->addData(
                        s->getNormalAddress(),
                        s->getVertexBufferSize());
            s->setNormalBufferOffset(offset);
            if (s->hasVertexColor()) {
                // add colors:
                offset = array_buffer->addData(
                            s->getColorAddress(),
                            s->getVertexBufferSize());
                s->setColorBufferOffset(offset);
            }
            if (s->hasUv()) {
                // add uvs:
                offset = array_buffer->addData(
                            s->getUvAddress(),
                            s->getUvBufferSize());
                s->setUvBufferOffset(offset);
            }
            // add indices:
            offset = index_buffer->addData(
                        s->getIndexAddress(),
                        s->getIndexBufferSize());
            s->setIndexBufferOffset(offset);

            if(is_setup) s->deleteVao();
            s->setVao(setupVAO(s));
        }
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

    if (s->hasVertexColor()) {
        glEnableVertexAttribArray(COLOR_IDX);
        glVertexAttribPointer(COLOR_IDX, 3, GL_FLOAT, GL_FALSE, 0, (void*)s->getColorBufferOffset());
    }

    if (s->hasUv()) {
        glEnableVertexAttribArray(UV_IDX);
        glVertexAttribPointer(UV_IDX, 2, GL_FLOAT, GL_FALSE, 0, (void*)s->getUvBufferOffset());
    }

    glBindBuffer(array_buffer->getType(), array_buffer->getID());
    glBindBuffer(index_buffer->getType(), index_buffer->getID());
    glBindVertexArray(0);
    return vao;
}
