#ifndef BASIC_EDITOR_H
#define BASIC_EDITOR_H

#include "editor.h"
/**
 * @brief Applies a random modification to the position (x,y,z) of each vertex and applies color depending on the new position.
 * This class allows to transform a generic icosphere into a simple planet
 */

class Basic_Editor : public Editor {
public:
    Basic_Editor(Shape* shape): Editor(shape) {}
    ~Basic_Editor();

    /**
     * @brief Applies vertex deplacement and colors the shape
     */
    void edit();

protected:

private:
    /**
     * @brief Assigns color for a vertex
     *
     * @param vertices Structure that contains the vertex data
     * @param colors : vector of 3 floats,
     * each float is a color of the vertex (red, green and blue).
     * Each float value is in [0,1].
     */
    void assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors);
};

#endif // BASIC_EDITOR_H


