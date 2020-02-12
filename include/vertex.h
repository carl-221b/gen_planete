#ifndef VERTEX_H
#define VERTEX_H

#include <Eigen/Geometry>

class Vertex
{
public:
    Vertex();

    Eigen::Vector3f getPosition();
};

#endif // VERTEX_H
