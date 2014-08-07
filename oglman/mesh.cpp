#include "mesh.h"
#include "camera.h"
#include "shaderman.h"
#include "bufferman.h"
#include "objreader.h"
#include "texture.h"

#include <glm/gtx/transform.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <cstring>
#include <iostream>

using glm::vec2;
using glm::vec3;
using glm::mat4;

const vec3 X_AXIS = vec3(1,0,0);
const vec3 Y_AXIS = vec3(0,1,0);
const vec3 Z_AXIS = vec3(0,0,1);

Camera *Mesh::active_cam = NULL;
BufferMan *Mesh::bufferman = NULL;

GLint Mesh::model_projection_loc;
GLint Mesh::model_world_loc;
GLint Mesh::normals_loc;
GLint Mesh::has_vertex_color_loc;
GLint Mesh::has_flat_color_loc;
GLint Mesh::has_texture_loc;
GLint Mesh::flat_color_loc;
GLint Mesh::has_wireframe_mode_loc;
GLint Mesh::wireframe_color_loc;
bool  Mesh::isWireframeMode;

vec3 Mesh::wireframe_color;

Mesh::Mesh() :
    isVertexColor(false),
    isFlatColor(false),
    isTextured(false),
    isInstanced(false),
{
    resetTransformations();
    DRAW_MODE = GL_TRIANGLES;

    bufferman->addShape(this);

    texture = nullptr;
}

Mesh::Mesh(Mesh *m) : Mesh()
{
    parent_mesh = m;
    isInstanced = true;
}

Mesh::Mesh(std::string path) : Mesh()
{
    ObjReader::loadOBJIndexed(path.c_str(),
                              vertices,
                              uvs,
                              normals,
                              indices);
}

Mesh::~Mesh()
{
    if (!isInstance()) deleteVao();
    if (texture != nullptr) { delete texture; }
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

    glUniform1f(has_vertex_color_loc, isVertexColor);
    glUniform1f(has_flat_color_loc, isFlatColor);
    glUniform1f(has_texture_loc, isTextured);
    glUniform1f(has_wireframe_mode_loc, isWireframeMode);

    if (isFlatColor) { glUniform3fv(flat_color_loc, 1, &flat_color[0]); }
    if (hasTexture()) { texture->use(); }

    glDrawElements(DRAW_MODE, getNumIndices(), GL_UNSIGNED_SHORT, (void*)getIndexBufferOffset());
    glBindVertexArray(0); // don't forget this!
}

void Mesh::setShaderMan(ShaderMan *man)
{
    model_projection_loc = man->getUniformLoc("modelToProjectionMatrix");
    model_world_loc = man->getUniformLoc("modelToWorldMatrix");
    normals_loc = man->getUniformLoc("normalMatrix");
    has_vertex_color_loc = man->getUniformLoc("hasVertexColor");
    has_flat_color_loc = man->getUniformLoc("hasFlatColor");
    has_texture_loc = man->getUniformLoc("hasTexture");
    flat_color_loc = man->getUniformLoc("flatColor");
    has_wireframe_mode_loc = man->getUniformLoc("hasWireframeMode");
    wireframe_color_loc = man->getUniformLoc("wireframeColor");

    Texture::setTextureSamplerLoc(man->getUniformLoc("textureSampler"));

    man->use();
}

GLsizeiptr Mesh::getArrayBufferSize() const
{
    // vertex and normal buffer size, which is the same:
    GLuint size = getVertexBufferSize() * 2;

    if (hasVertexColor()) { size += getVertexBufferSize(); }
    if (hasUv())          { size += getUvBufferSize(); }

    return size;
}

void Mesh::updateWorldMatrix()
{
    // rotation order is XYZ, for now...
    world_matrix =
            glm::translate(vec3(translateX, translateY, translateZ)) *
            glm::rotate(rotateZ, Z_AXIS) *
            glm::rotate(rotateY, Y_AXIS) *
            glm::rotate(rotateX, X_AXIS) *
            glm::scale(vec3(scale));
}

void Mesh::resetTransformations()
{
    world_matrix = glm::mat4();
    rotateX = rotateY = rotateZ
            = translateX = translateY = translateZ = 0;
    scale = 1;
}

bool Mesh::isInstance() const
{
    return isInstanced;
}

void Mesh::setupInstance()
{
    vao = parent_mesh->getVao();
}

vec3 Mesh::getWireframeColor()
{
    return wireframe_color;
}

void Mesh::setWireframeColor(const vec3 &value)
{
    wireframe_color = value;
    glUniform3fv(wireframe_color_loc, 1, &wireframe_color[0]);
}

void Mesh::setTexture(const std::string &path)
{
    texture = new Texture(path);
    enableTexture();
}

GLsizeiptr Mesh::getVertexBufferSize() const
{
    return vertices.size() * sizeof(vec3);
}

GLsizeiptr Mesh::getUvBufferSize() const
{
    return uvs.size() * sizeof(vec2);
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

const glm::vec2 *Mesh::getUvAddress() const
{
    return uvs.data();
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

void Mesh::setUvBufferOffset(GLuint offset)
{
    uv_buffer_offset = offset;
}

GLuint Mesh::getIndexBufferOffset() const
{
    if (isInstance()) return parent_mesh->getIndexBufferOffset();

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

GLuint Mesh::getUvBufferOffset() const
{
    return uv_buffer_offset;
}

GLuint Mesh::getNumIndices() const
{
    if (isInstance()) return parent_mesh->getNumIndices();

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

void Mesh::setDrawMode(const GLenum &mode)
{
    DRAW_MODE = mode;
}

void Mesh::setWorldMatrix(const mat4 &mat)
{
    world_matrix = mat;
    normal_matrix = glm::transpose(glm::inverse(world_matrix));
}

void Mesh::setCamera(Camera *c)
{
    active_cam = c;
}

void Mesh::setBufferMan(BufferMan *man)
{
    bufferman = man;
}

void Mesh::setWireframeMode(bool val)
{
    isWireframeMode = val;
}

GLfloat Mesh::getScale() const
{
    return scale;
}

void Mesh::setScale(const GLfloat &value)
{
    scale = value;
    updateWorldMatrix();
}

GLfloat Mesh::getRotateX() const
{
    return rotateX;
}

void Mesh::setRotateX(const GLfloat &value)
{
    rotateX = value;
    updateWorldMatrix();
}
GLfloat Mesh::getRotateY() const
{
    return rotateY;
}

void Mesh::setRotateY(const GLfloat &value)
{
    rotateY = value;
    updateWorldMatrix();
}
GLfloat Mesh::getRotateZ() const
{
    return rotateZ;
}

void Mesh::setRotateZ(const GLfloat &value)
{
    rotateZ = value;
    updateWorldMatrix();
}

GLfloat Mesh::getTranslateX() const
{
    return translateX;
}

void Mesh::setTranslateX(const GLfloat &value)
{
    translateX = value;
    updateWorldMatrix();
}
GLfloat Mesh::getTranslateY() const
{
    return translateY;
}

void Mesh::setTranslateY(const GLfloat &value)
{
    translateY = value;
    updateWorldMatrix();
}
GLfloat Mesh::getTranslateZ() const
{
    return translateZ;
}

void Mesh::setTranslateZ(const GLfloat &value)
{
    translateZ = value;
    updateWorldMatrix();
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

bool Mesh::hasUv() const
{
    return !uvs.empty();
}
bool Mesh::hasTexture() const
{
    return isTextured;
}

void Mesh::enableTexture()
{
    isTextured = true;
}

void Mesh::disableTexture()
{
    isTextured = false;
}
