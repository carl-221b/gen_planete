#ifndef ADVANCED_EDITOR_H
#define ADVANCED_EDITOR_H

#include "editor.h"

/**
 * @brief Applies a random modification to the position (x,y,z) of each vertex and applies color depending on the new position.
 * This class allows to transform a generic icosphere into a simple planet
 */

class Advanced_Editor : public Editor {
public:
    Advanced_Editor(Shape* shape): Editor(shape) {}
    ~Advanced_Editor();

    /**
     * @brief Applies vertex deplacement and colors the shape
     */

    void edit();

private:
    /**
     * @brief Assigns color for a vertex
     *
     * @param vertices Structure that contains the vertex data
     * @param r Value in [0,1] for the red channel of the vertex
     * @param g Value in [0,1] for the green channel of the vertex
     * @param b Value in [0,1] for the blue channel of the vertex
     */

    void assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors);
};

#endif // Advanced_Editor_H
