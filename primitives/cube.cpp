#include "cube.h"

using glm::vec3;

Cube::Cube()
{
}

void Cube::store()
{
    vec3 stackVerts[] =
    {
        vec3(-1.0f, +1.0f, +1.0f),  // 0
        vec3(+1.0f, +1.0f, +1.0f),  // 1
        vec3(+1.0f, +1.0f, -1.0f),  // 2
        vec3(-1.0f, +1.0f, -1.0f),  // 3
        vec3(-1.0f, +1.0f, -1.0f),  // 4
        vec3(+1.0f, +1.0f, -1.0f),  // 5
        vec3(+1.0f, -1.0f, -1.0f),  // 6
        vec3(-1.0f, -1.0f, -1.0f),  // 7
        vec3(+1.0f, +1.0f, -1.0f),  // 8
        vec3(+1.0f, +1.0f, +1.0f),  // 9
        vec3(+1.0f, -1.0f, +1.0f),  // 10
        vec3(+1.0f, -1.0f, -1.0f),  // 11
        vec3(-1.0f, +1.0f, +1.0f),  // 12
        vec3(-1.0f, +1.0f, -1.0f),  // 13
        vec3(-1.0f, -1.0f, -1.0f),  // 14
        vec3(-1.0f, -1.0f, +1.0f),  // 15
        vec3(+1.0f, +1.0f, +1.0f),  // 16
        vec3(-1.0f, +1.0f, +1.0f),  // 17
        vec3(-1.0f, -1.0f, +1.0f),  // 18
        vec3(+1.0f, -1.0f, +1.0f),  // 19
        vec3(+1.0f, -1.0f, -1.0f),  // 20
        vec3(-1.0f, -1.0f, -1.0f),  // 21
        vec3(-1.0f, -1.0f, +1.0f),  // 22
        vec3(+1.0f, -1.0f, +1.0f),  // 23
    };
    vec3 stackNormals[] =
    {
        vec3(+0.0f, +1.0f, +0.0f),
        vec3(+0.0f, +1.0f, +0.0f),
        vec3(+0.0f, +1.0f, +0.0f),
        vec3(+0.0f, +1.0f, +0.0f),
        vec3(+0.0f, +0.0f, -1.0f),
        vec3(+0.0f, +0.0f, -1.0f),
        vec3(+0.0f, +0.0f, -1.0f),
        vec3(+0.0f, +0.0f, -1.0f),
        vec3(+1.0f, +0.0f, +0.0f),
        vec3(+1.0f, +0.0f, +0.0f),
        vec3(+1.0f, +0.0f, +0.0f),
        vec3(+1.0f, +0.0f, +0.0f),
        vec3(-1.0f, +0.0f, +0.0f),
        vec3(-1.0f, +0.0f, +0.0f),
        vec3(-1.0f, +0.0f, +0.0f),
        vec3(-1.0f, +0.0f, +0.0f),
        vec3(+0.0f, +0.0f, +1.0f),
        vec3(+0.0f, +0.0f, +1.0f),
        vec3(+0.0f, +0.0f, +1.0f),
        vec3(+0.0f, +0.0f, +1.0f),
        vec3(+0.0f, -1.0f, +0.0f),
        vec3(+0.0f, -1.0f, +0.0f),
        vec3(+0.0f, -1.0f, +0.0f),
        vec3(+0.0f, -1.0f, +0.0f),
    };
    GLushort stackIndices[] = {
        0,   1,  2,  0,  2,  3, // Top
        4,   5,  6,  4,  6,  7, // Front
        8,   9, 10,  8, 10, 11, // Right
        12, 13, 14, 12, 14, 15, // Left
        16, 17, 18, 16, 18, 19, // Back
        20, 22, 21, 20, 23, 22, // Bottom
    };

    STORE_VERTICES(stackVerts);
    STORE_NORMALS(stackNormals);
    STORE_INDICES(stackIndices);
}
