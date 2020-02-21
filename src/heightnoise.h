#ifndef HEIGHTNOISE_H
#define HEIGHTNOISE_H

#include <Eigen/Geometry>

/**
 * @brief The HeightNoise class generate noise.
 */
class HeightNoise
{
public:
    HeightNoise();
    ~HeightNoise();
    /**
     * @brief getValue get the value noise.
     * @param keygen THe key of the generation.
     * @return the value noise in float associated to the key.
     * Domain between [-1, 1]
     */
    float getValue(const Eigen::Vector3f &keygen);
};

#endif // HEIGHTNOISE_H
