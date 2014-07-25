#include "mesh.h"
#include "camera.h"
#include "shaderman.h"
#include "bufferman.h"

#include <cstring>

using glm::vec3;
using glm::mat4;

Camera *Mesh::active_cam = NULL;
BufferMan *Mesh::bufferman = NULL;

GLint Mesh::model_projection_loc;
GLint Mesh::model_world_loc;
GLint Mesh::normals_loc;
GLint Mesh::has_vertex_color_loc;
GLint Mesh::has_flat_color_loc;
GLint Mesh::flat_color_loc;

Mesh::Mesh()
{
    glewInit();

    setWorldMatrix(glm::mat4());
    DRAW_MODE = GL_TRIANGLES;

    bufferman->addShape(this);
    isVertexColor = false;
    isFlatColor = false;
}

Mesh::~Mesh()
{
    deleteVao();
}

void Mesh::draw()
{
    mat4 model2projection = active_cam->getViewProjectionMatrix() * world_matrix;

    glBindVertexArray(vao);
    glUniformMatrix4fv(normals_loc, 1,
                       GL_FALSE, &normal_matrix[0][0]);
    glUniformMatrix4fv(model_world_loc, 1,
                       GL_FALSE, &world_matrix[0][0]);
    glUniformMatrix4fv(model_projection_loc, 1,
                       GL_FALSE, &model2projection[0][0]);

    if(hasVertexColor()) {
        glUniform1f(has_vertex_color_loc, GL_TRUE);
    } else {
        glUniform1f(has_vertex_color_loc, GL_FALSE);
    }

    if (hasFlatColor()) {
        glUniform1f(has_flat_color_loc, GL_TRUE);
        glUniform3fv(flat_color_loc, 1, &flat_color[0]);
    } else {
        glUniform1f(has_flat_color_loc, GL_FALSE);
    }

    glDrawElements(DRAW_MODE, indices.size(), GL_UNSIGNED_SHORT, (void*)index_buffer_offset);
}

GLsizeiptr Mesh::getVertexBufferSize() const
{
    GLuint size = vertices.size() + normals.size();

    if (hasVertexColor()) { size += colors.size(); }

    return (size) * sizeof(vec3);
}

GLsizeiptr Mesh::getVertexBufferSubSize() const
{
    return vertices.size() * sizeof(vec3);
}

GLsizeiptr Mesh::getIndexBufferSize() const
{
    return indices.size() * sizeof(GLushort);
}

const glm::vec3 *Mesh::getVertexAddress() const
{
    return vertices.data();
}

const vec3 *Mesh::getNormalAddress() const
{
    return normals.data();
}

const glm::vec3 *Mesh::getColorAddress() const
{
    return colors.data();
}

const GLushort *Mesh::getIndexAddress() const
{
    return indices.data();
}

void Mesh::setIndexBufferOffset(GLuint offset)
{
    index_buffer_offset = offset;
}

void Mesh::setVertexBufferOffset(GLuint offset)
{
    vertex_buffer_offset = offset;
}

void Mesh::setNormalBufferOffset(GLuint offset)
{
    normal_buffer_offset = offset;
}

void Mesh::setColorBufferOffset(GLuint offset)
{
    color_buffer_offset = offset;
}

GLuint Mesh::getIndexBufferOffset() const
{
    return index_buffer_offset;
}

GLuint Mesh::getVertexBufferOffset() const
{
    return vertex_buffer_offset;
}

GLuint Mesh::getNormalBufferOffset() const
{
    return normal_buffer_offset;
}

GLuint Mesh::getColorBufferOffset() const
{
    return color_buffer_offset;
}

GLuint Mesh::getNumIndices() const
{
    return indices.size();
}

GLuint Mesh::getNumVertices() const
{
    return vertices.size();
}

GLuint Mesh::getVao() const
{
    return vao;
}

void Mesh::setVao(GLuint v)
{
    vao = v;
}

void Mesh::deleteVao()
{
    glDeleteVertexArrays(1, &vao);
}

void Mesh::setDrawMode(GLenum mode)
{
    DRAW_MODE = mode;
}

void Mesh::setWorldMatrix(glm::mat4 mat)
{
    world_matrix = mat;
    normal_matrix = glm::transpose(glm::inverse(world_matrix));
}

void Mesh::setCamera(Camera *c)
{
    active_cam = c;
}

void Mesh::setShaderMan(ShaderMan *man)
{
    model_projection_loc = man->getUniformLoc("modelToProjectionMatrix");
    model_world_loc = man->getUniformLoc("modelToWorldMatrix");
    normals_loc = man->getUniformLoc("normalMatrix");
    has_vertex_color_loc = man->getUniformLoc("hasVertexColor");
    has_flat_color_loc = man->getUniformLoc("hasFlatColor");
    flat_color_loc = man->getUniformLoc("flatColor");
    man->use();
}

void Mesh::setBufferMan(BufferMan *man)
{
    bufferman = man;
}

void Mesh::enableVertexColor()
{
    isVertexColor = true;
}

void Mesh::disableVertexColor()
{
    isVertexColor = false;
}

bool Mesh::hasVertexColor() const
{
    return isVertexColor;
}

void Mesh::enableFlatColor()
{
    isFlatColor = true;
}

void Mesh::disableFlatColor()
{
    isFlatColor = false;
}

bool Mesh::hasFlatColor() const
{
    return isFlatColor;
}

void Mesh::setFlatColor(const glm::vec3 &color)
{
    flat_color = color;
}

glm::vec3 Mesh::getFlatColor() const
{
    return flat_color;
}



