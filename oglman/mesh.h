#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glew.h>
#include <vector>
#include <glm/glm.hpp>

#define PROCESS_ARRAY(a, v) v.insert(v.end(), &a[0], &a[sizeof(a)/sizeof(*a)]);
#define STORE_VERTICES(v) PROCESS_ARRAY(v, vertices);
#define STORE_NORMALS(n)  PROCESS_ARRAY(n, normals);
#define STORE_INDICES(i)  PROCESS_ARRAY(i, indices);

using glm::vec3;
using glm::mat4;

// forward class
class ShaderMan;
class Camera;
class BufferMan;

class Mesh
{
public:
    Mesh();
    virtual ~Mesh();
    virtual void store() {}
    void draw();

    GLsizeiptr getVertexBufferSize() const;
    GLsizeiptr getVertexBufferSubSize() const;
    GLsizeiptr getIndexBufferSize() const;

    const vec3* getVertexAddress() const;
    const glm::vec3* getNormalAddress() const;
    const GLushort* getIndexAddress() const;

    void setIndexBufferOffset(GLuint offset);
    void setVertexBufferOffset(GLuint offset);
    void setNormalBufferOffset(GLuint offset);

    GLuint getIndexBufferOffset() const;
    GLuint getVertexBufferOffset() const;
    GLuint getNormalBufferOffset() const;

    GLuint getNumIndices() const;
    GLuint getNumVertices() const;

    GLuint getVao() const;
    void setVao(GLuint v);

    void setDrawMode(GLenum mode);
    void setWorldMatrix(mat4 mat);

    static void setCamera(Camera *c);
    static void setShaderMan(ShaderMan *man);
    static void setBufferMan(BufferMan *man);

protected:
    std::vector<vec3> vertices;
    std::vector<vec3> normals;
    std::vector<GLushort> indices;

private:
    GLuint vao;
    GLenum DRAW_MODE;
    GLuint index_buffer_offset;
    GLuint vertex_buffer_offset;
    GLuint normal_buffer_offset;

    mat4 world_matrix;
    mat4 normal_matrix;

    static GLint model_projection_loc;
    static GLint model_world_loc;
    static GLint normals_loc;

    static Camera *active_cam;
    static BufferMan *bufferman;
};

#endif // SHAPE_H
