#ifndef EDITOR_H
#define EDITOR_H

#include "shape.h"
#include <Eigen/Geometry>

/**
 * @brief Interface to be implemented by an editor that will transform a generic icosphere into a given type of planet
 * 
 */

class Editor /*: public Shape*/ {
public:
    Editor(Shape* shape) {_shape = shape;}
    virtual ~Editor() {}
    /**
     * @brief Applies vertex deplacement and colors the shape
     * 
     */
    virtual void edit() = 0;

protected:
    Shape* _shape;
};

#endif // EDITOR_H
