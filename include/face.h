#ifndef FACE_H
#define FACE_H

#include <vertex.h>
#include <vector>

class Face
{
public:
    Face();

    /**
     * @brief normal, get the normal of the face.
     * @return
     */
    Eigen::Vector3f normal();

    /**
     * @brief getVertice, get all he vertice of the face.
     * Ordered in the trigonometric order.
     * @return the vector associated.
     */
    /*const*/ std::vector<Vertex> getVertice() const;

    /**
     * @brief getId, get the id of the face.
     * @return the id.
     */
    int getId();

private:

    int m_id;

};

#endif // FACE_H
