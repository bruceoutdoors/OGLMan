/**

modified Obj loader from http://www.opengl-tutorial.org/

Very, VERY simple OBJ loader.
Here is a short list of features a real function would provide :
- Binary files. Reading a model should be just a few memcpy's away, not parsing a file at runtime. In short : OBJ is not very great.
- Animations & bones (includes bones weights)
- Multiple UVs
- All attributes should be optional, not "forced"
- More stable. Change a line in the OBJ file and it crashes.
- More secure. Change another line and you can inject code.
- Loading from memory, stream, etc

**/

#ifndef OBJREADER_H
#define OBJREADER_H


#include <vector>
#include <glm/glm.hpp>

using std::vector;
using glm::vec3;
using glm::vec2;

class ObjReader
{
public:
    static bool loadOBJ(const char *path,
        vector<vec3> &out_vertices,
        vector<vec2> &out_uvs,
        vector<vec3> &out_normals);

    static bool loadOBJIndexed(const char *path,
                        vector<vec3> &out_vertices,
                        vector<vec2> &out_uvs,
                        vector<vec3> &out_normals,
                        vector<unsigned short> &out_indices);

private:
    static void indexVBO(
        vector<vec3> &in_vertices,
        vector<vec2> &in_uvs,
        vector<vec3> &in_normals,

        vector<unsigned short> &out_indices,
        vector<vec3> &out_vertices,
        vector<vec2> &out_uvs,
        vector<vec3> &out_normals
    );

};

#endif // OBJREADER_H
