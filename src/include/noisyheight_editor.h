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
    NoisyHeight_Editor(Shape* shape, int octave, float frequence, float persistence);
    ~NoisyHeight_Editor();

    void edit();

protected:

private:
    void assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors);

    int _octave;
    float _frequence;
    float _persistence;
};

#endif // NOISYHEIGHT_EDITOR_H
