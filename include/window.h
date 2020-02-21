#ifndef WINDOW_H
#define WINDOW_H

#include <renderer.h>

class Window
{
public:
    Window();

    Windows(Planet& planet);

    void OnMouseEnter();

    void OnKeyPressed(int /*key*/);
};

#endif // WINDOW_H
