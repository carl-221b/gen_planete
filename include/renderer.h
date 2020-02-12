#ifndef RENDERER_H
#define RENDERER_H

#include <planet.h>

#include <camera.h>

class Renderer
{
public:

    Renderer(Planet planet);

    /**
     * @brief drawScene, draw the actual scene with the bacground, the planet, calculation of the camera, etc.
     */
    void drawScene();

private:

};

#endif // RENDERER_H
