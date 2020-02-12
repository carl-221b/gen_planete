#ifndef GEOMETRY_H
#define GEOMETRY_H

#include <face.h>

class Geometry
{
public:
    Geometry();

    /**
     * @brief Build the default geometry implemented.
     */
    void Build();

    /**
     * @brief getFace, get a face by his id..
     * @param id the identifier of the face
     * @return the face associated.
     */
    Face getFace(int id) const;

    /**
     * @brief getSizeFaces, get the actual number of faces.
     * @return an integer.
     */
    int getSizeFaces() const;
};

#endif // GEOMETRY_H
