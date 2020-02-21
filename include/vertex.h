#ifndef VERTEX_H
#define VERTEX_H

#include <Eigen/Geometry>

class Vertex
{
public:
    Vertex();

    /**
     * @brief getPosition, get the position of the vertex.
     * @return A vector3f.
     */
    Eigen::Vector3f getPosition();
};

#endif // VERTEX_H
