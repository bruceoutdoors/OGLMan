#include "objreader.h"
#include <stdio.h>
#include <map>
#include <cstring>

using std::vector;
using glm::vec3;
using glm::vec2;

struct PackedVertex {
    vec3 position;
    vec2 uv;
    vec3 normal;
    bool operator<(const PackedVertex &that) const
    {
        return memcmp((void *)this, (void *)&that, sizeof(PackedVertex)) > 0;
    }
};

bool ObjReader::loadOBJ(const char *path,
                        vector<vec3> &out_vertices,
                        vector<vec2> &out_uvs,
                        vector<vec3> &out_normals)
{
    vector<unsigned int> vertexIndices, uvIndices, normalIndices;
    vector<vec3> temp_vertices;
    vector<vec2> temp_uvs;
    vector<vec3> temp_normals;


    FILE *file = fopen(path, "r");
    if (file == NULL) {
        printf("Impossible to open the file ! Are you in the right path ? See Tutorial 1 for details\n");
        getchar();
        return false;
    }

    while (true) {
        char lineHeader[128];
        // read the first word of the line
        int res = fscanf(file, "%127s", lineHeader);
        if (res == EOF)
            break; // EOF = End Of File. Quit the loop.

        // else : parse lineHeader

        if (strcmp(lineHeader, "v") == 0) {
            vec3 vertex;
            fscanf(file, "%f %f %f\n", &vertex.x, &vertex.y, &vertex.z);
            temp_vertices.push_back(vertex);
        } else if (strcmp(lineHeader, "vt") == 0) {
            vec2 uv;
            fscanf(file, "%f %f\n", &uv.x, &uv.y);
            uv.y = -uv.y; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
            temp_uvs.push_back(uv);
        } else if (strcmp(lineHeader, "vn") == 0) {
            vec3 normal;
            fscanf(file, "%f %f %f\n", &normal.x, &normal.y, &normal.z);
            temp_normals.push_back(normal);
        } else if (strcmp(lineHeader, "f") == 0) {
            unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
            int matches = fscanf(file, "%u/%u/%u %u/%u/%u %u/%u/%u\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2]);
            if (matches != 9) {
                printf("File can't be read by our simple parser :-( Try exporting with other options\n");
                return false;
            }
            vertexIndices.push_back(vertexIndex[0]);
            vertexIndices.push_back(vertexIndex[1]);
            vertexIndices.push_back(vertexIndex[2]);
            uvIndices    .push_back(uvIndex[0]);
            uvIndices    .push_back(uvIndex[1]);
            uvIndices    .push_back(uvIndex[2]);
            normalIndices.push_back(normalIndex[0]);
            normalIndices.push_back(normalIndex[1]);
            normalIndices.push_back(normalIndex[2]);
        } else {
            // Probably a comment, eat up the rest of the line
            char stupidBuffer[1000];
            fgets(stupidBuffer, 1000, file);
        }

    }

    fclose(file);

    // For each vertex of each triangle
    for (unsigned int i = 0; i < vertexIndices.size(); i++) {

        // Get the indices of its attributes
        unsigned int vertexIndex = vertexIndices[i];
        unsigned int uvIndex = uvIndices[i];
        unsigned int normalIndex = normalIndices[i];

        // Get the attributes thanks to the index
        vec3 vertex = temp_vertices[ vertexIndex - 1 ];
        vec2 uv = temp_uvs[ uvIndex - 1 ];
        vec3 normal = temp_normals[ normalIndex - 1 ];

        // Put the attributes in buffers
        out_vertices.push_back(vertex);
        out_uvs     .push_back(uv);
        out_normals .push_back(normal);

    }

    return true;
}

bool ObjReader::loadOBJIndexed(
    const char *path,
    vector<glm::vec3> &out_vertices,
    vector<glm::vec2> &out_uvs,
    vector<glm::vec3> &out_normals,
    vector<unsigned short> &out_indices)
{
    vector<glm::vec3> temp_out_vertices;
    vector<glm::vec2> temp_out_uvs;
    vector<glm::vec3> temp_out_normals;

    loadOBJ(path, temp_out_vertices, temp_out_uvs, temp_out_normals);

    indexVBO(temp_out_vertices,
             temp_out_uvs,
             temp_out_normals,

             out_indices,
             out_vertices,
             out_uvs,
             out_normals);

    return true;
}

bool getSimilarVertexIndex_fast(
    PackedVertex &packed,
    std::map<PackedVertex, unsigned short> &VertexToOutIndex,
    unsigned short &result)
{
    std::map<PackedVertex, unsigned short>::iterator it = VertexToOutIndex.find(packed);
    if (it == VertexToOutIndex.end()) {
        return false;
    } else {
        result = it->second;
        return true;
    }
}

void ObjReader::indexVBO(
    vector<vec3> &in_vertices,
    vector<vec2> &in_uvs,
    vector<vec3> &in_normals,
    vector<unsigned short> &out_indices,
    vector<vec3> &out_vertices,
    vector<vec2> &out_uvs,
    vector<vec3> &out_normals)
{
    std::map<PackedVertex, unsigned short> VertexToOutIndex;

    // For each input vertex
    for (unsigned int i = 0; i < in_vertices.size(); i++) {

        PackedVertex packed = {in_vertices[i], in_uvs[i], in_normals[i]};


        // Try to find a similar vertex in out_XXXX
        unsigned short index;
        bool found = getSimilarVertexIndex_fast(packed, VertexToOutIndex, index);

        if (found) {  // A similar vertex is already in the VBO, use it instead !
            out_indices.push_back(index);
        } else { // If not, it needs to be added in the output data.
            out_vertices.push_back(in_vertices[i]);
            out_uvs     .push_back(in_uvs[i]);
            out_normals .push_back(in_normals[i]);
            unsigned short newindex = (unsigned short)out_vertices.size() - 1;
            out_indices .push_back(newindex);
            VertexToOutIndex[ packed ] = newindex;
        }
    }
}


