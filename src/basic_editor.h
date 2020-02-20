#ifndef BASIC_EDITOR_H
#define BASIC_EDITOR_H

#include "editor.h"

class Basic_Editor : public Editor {
public:
    Basic_Editor(Shape* shape) {_shape = shape;} /*: Editor(shape) {}*/
    ~Basic_Editor();

    void edit();

protected:

private:
    void assignColor(Shape::Vertices* vertices, float r, float g, float b);
};

#endif // BASIC_EDITOR_H
