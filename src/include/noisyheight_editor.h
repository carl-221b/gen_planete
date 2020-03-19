#ifndef NOISYHEIGHT_EDITOR_H
#define NOISYHEIGHT_EDITOR_H

#include "editor.h"
#include "heightnoise.h"

/**
 * @brief The NoisyHeight_Editor class permit to use a noise in order to displace vertices
 * and apply a color from the resulting height.
 */
class NoisyHeight_Editor : public Editor
{
public:
    NoisyHeight_Editor(Shape* shape);
    NoisyHeight_Editor(Shape* shape, int octave, int frequence, int persistence);
    ~NoisyHeight_Editor();

    void edit();

protected:

private:
    void assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors);

    int _octave;
    int _frequence;
    int _persistence;
};

#endif // NOISYHEIGHT_EDITOR_H
