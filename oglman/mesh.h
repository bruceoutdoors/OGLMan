#ifndef SHAPE_H
#define SHAPE_H

#include <GL/glew.h>
#include <vector>
#include <string>
#include <glm/glm.hpp>

#define PROCESS_ARRAY(a, v) v.insert(v.end(), &a[0], &a[sizeof(a)/sizeof(*a)]);
#define STORE_VERTICES(v) PROCESS_ARRAY(v, vertices);
#define STORE_NORMALS(n)  PROCESS_ARRAY(n, normals);
#define STORE_COLORS(c)   PROCESS_ARRAY(c, colors);
#define STORE_INDICES(i)  PROCESS_ARRAY(i, indices);

using glm::vec2;
using glm::vec3;
using glm::mat4;
using std::vector;

// forward class
class ShaderMan;
class Camera;
class BufferMan;
class Texture;

class Mesh
{
public:
    Mesh();
    Mesh(std::string path);
    virtual ~Mesh();
    virtual void store() {}
    void draw();

    GLsizeiptr getArrayBufferSize() const;
    GLsizeiptr getVertexBufferSize() const;
    GLsizeiptr getUvBufferSize() const;
    GLsizeiptr getIndexBufferSize() const;

    const vec3* getVertexAddress() const;
    const vec3* getNormalAddress() const;
    const vec3* getColorAddress() const;
    const GLushort* getIndexAddress() const;
    const vec2* getUvAddress() const;

    void setIndexBufferOffset(GLuint offset);
    void setVertexBufferOffset(GLuint offset);
    void setNormalBufferOffset(GLuint offset);
    void setColorBufferOffset(GLuint offset);
    void setUvBufferOffset(GLuint offset);

    GLuint getIndexBufferOffset() const;
    GLuint getVertexBufferOffset() const;
    GLuint getNormalBufferOffset() const;
    GLuint getColorBufferOffset() const;
    GLuint getUvBufferOffset() const;

    GLuint getNumIndices() const;
    GLuint getNumVertices() const;

    GLuint getVao() const;
    void setVao(GLuint v);
    void deleteVao();

    void setDrawMode(const GLenum &mode);
    void setWorldMatrix(const mat4 &mat);

    void enableVertexColor();
    void disableVertexColor();
    bool hasVertexColor() const;

    void enableFlatColor();
    void disableFlatColor();
    bool hasFlatColor() const;
    void setFlatColor(const vec3 &color);
    vec3 getFlatColor() const;

    bool hasUv() const;

    void setTexture(const std::string &path);
    bool hasTexture() const;
    void enableTexture();
    void disableTexture();

    static void setCamera(Camera *c);
    static void setShaderMan(ShaderMan *man);
    static void setBufferMan(BufferMan *man);

    static void enableWirefameMode();
    static void disableWirefameMode();
    static bool hasWireframeMode();

protected:
    vector<vec3> vertices;
    vector<vec3> colors;
    vector<vec3> normals;
    vector<vec2> uvs;
    vector<GLushort> indices;

private:
    GLuint vao;
    GLenum DRAW_MODE;
    GLuint index_buffer_offset;
    GLuint vertex_buffer_offset;
    GLuint normal_buffer_offset;
    GLuint color_buffer_offset;
    GLuint uv_buffer_offset;

    bool isVertexColor;
    bool isFlatColor;
    bool isTextured;

    Texture *texture;

    vec3 flat_color;

    mat4 world_matrix;
    mat4 normal_matrix;

    static GLint model_projection_loc;
    static GLint model_world_loc;
    static GLint normals_loc;
    static GLint has_vertex_color_loc;
    static GLint has_flat_color_loc;
    static GLint has_texture_loc;
    static GLint flat_color_loc;
    static bool isWireframeMode;

    static Camera *active_cam;
    static BufferMan *bufferman;
};

#endif // SHAPE_H
