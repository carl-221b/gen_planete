#ifndef NOISYHEIGHT_EDITOR_H
#define NOISYHEIGHT_EDITOR_H

#include "editor.h"

#include <iostream>
#include <noise/noise.h>

class NoisyHeight_Editor : public Editor
{
public:
    NoisyHeight_Editor(Shape* shape): Editor(shape) {}
    ~NoisyHeight_Editor();

    void edit();

protected:

private:
    void assignColor(Shape::Vertices* vertices, float r, float g, float b);
};

#endif // NOISYHEIGHT_EDITOR_H
