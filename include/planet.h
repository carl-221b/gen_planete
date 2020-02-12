#ifndef PLANET_H
#define PLANET_H

#include <geometry.h>

#include <editor.h>

typedef Eigen::Matrix<uint,3,1> Vector3ui;

class Planet
{
public:
    Planet();

    /**
     * @brief edit, apply transformations to the geometry and the colors.
     * @param ed the editor used.
     */
    void edit(Editor& ed);

    /**
     * @brief draw the planet.
     */
    void draw();

    /**
     * @brief getFaceColor, get the color of the face.
     * @param indexFace the index of the face.
     * @return a string representing the color.
     */
    std::string getFaceColor(uint indexFace) const;

    /**
     * @brief setColor, set the color represented by a key.
     * @param key to set.
     */
    void setColor(std::string key);

    /**
     * @brief getColor, get the color with a key.
     * @param key the identifier
     * @return a vector3 of unsigned int in RGB.
     */
    Vector3ui getColor(std::string key) const;
};

#endif // PLANET_H
