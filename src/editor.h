#ifndef EDITOR_H
#define EDITOR_H

#include "shape.h"
#include <Eigen/Geometry>

class Editor /*: public Shape*/ {
public:
    Editor() {}
    virtual ~Editor() {}

    virtual void edit() = 0;

protected:
    Shape* _shape;
};

#endif // EDITOR_H
