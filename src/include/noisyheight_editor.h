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
    NoisyHeight_Editor(Shape* shape, double octave, double frequence, double persistence);
    ~NoisyHeight_Editor();

    virtual void edit();

    virtual std::string info() const;

protected:

private:
    void assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors);
    double _octave;
    double _frequence;
    double _persistence;
    //double _seed;
};

#endif // NOISYHEIGHT_EDITOR_H
