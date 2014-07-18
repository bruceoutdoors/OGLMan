#ifndef PLANE_H
#define PLANE_H

#include "oglman/mesh.h"

class Plane : public Mesh
{
public:
    Plane(unsigned int dimensions = 10);

private:
    void makeVerts(unsigned int dimensions);
    void makeIndices(unsigned int dimensions);
    unsigned int dimensions;
};

#endif // PLANE_H
