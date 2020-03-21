#ifndef NOISYHEIGHT_EDITOR_H
#define NOISYHEIGHT_EDITOR_H

#include "editor.h"
#include "noiserandom.h"
#include "aleatorymode.h"

/**
 * @brief The NoisyHeight_Editor class permit to use a noise in order to displace vertices
 * and apply a color from the resulting height.
 */
class NoisyHeight_Editor : public Editor
{
public:

    /**
     * @brief NoisyHeight_Editor
     * @param shape the shape to modify.
     * @param maximum_displacement_ratio the maximum displacement factor, determine the height
     * of montains relative to the planet radius.
     * @param flags the different flags in order to aleatory pick parameters.
     * Combine like for example ALEA_OCTAVE | ALEA_SEED.
     * The available for this editor :
     *          NO_ALEATORY
     *          ALEA_OCTAVE
     *          ALEA_FREQUENCE
     *          ALEA_PERSISTENCE
     *          ALEA_SEED
     * @param octave
     * @param frequence
     * @param persistence
     * @param seed
     * @param layers the colors with associated bounds of heights.
     */
    NoisyHeight_Editor(Shape* shape,
                       double maximum_displacement_ratio,
                       Mode_Aleatory_Flags flags,
                       int octave,
                       double frequence,
                       double persistence,
                       int seed,
                       ColorThresholdTable *layers = nullptr);

    NoisyHeight_Editor(Shape* shape);

    ~NoisyHeight_Editor();

    virtual void edit();

    virtual std::string info() const;

protected:

    void assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors);

private:
    double _maximum_displacement_ratio;
    int _octave;

    double _frequence;
    double _persistence;
    int _seed;
    ColorThresholdTable* _layers;
};

#endif // NOISYHEIGHT_EDITOR_H
