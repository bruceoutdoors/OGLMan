#ifndef PLANE_H
#define PLANE_H

/**
  * the algorithm to generate this plane originated
  * from Jamie King's YouTube OpenGL tutorials:
  *
  *   http://bit.ly/1t2Rxde
  *
  * Check'em out. They're awesum! :D
  *
  **/

#include "oglman/mesh.h"

class Plane : public Mesh
{
public:
    Plane(unsigned int subdv = 10);

private:
    void makeVerts(unsigned int subdv);
    void makeIndices(unsigned int subdv);
    unsigned int subdv;
};

#endif // PLANE_H
