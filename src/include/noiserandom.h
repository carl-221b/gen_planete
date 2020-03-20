#ifndef HEIGHTNOISE_H
#define HEIGHTNOISE_H

#include <Eigen/Geometry>
#include <random>
#include <noise/noise.h>

namespace NoiseRandom
{

#define CLAMP_EPSILON 10e-6

/**
 * @brief random
 * @return a random number. value between [-1, 1]
 */
double random();

/**
 * @brief normalRandom
 * @param mean the mean of the normal law
 * @param deviation the deviation of the norma law
 * @return a normal random number thyat suit to the normal law.
 */
double normalRandom(double mean, double deviation);

/**
 * @brief The HeightNoise class generate noise.
 */
class HeightNoise
{

public:

    HeightNoise(int seed, int frequence, int octave, int persistence);
    ~HeightNoise();
    /**
     * @brief getValue get the value noise.
     * @param keygen THe key of the generation.
     * @return the value noise in float associated to the key.
     * Domain between [-1, 1]
     */
    double getValue(const Eigen::Vector3f &keygen);

private:
    noise::module::Perlin _generator;
    noise::module::Clamp _out;
};

}



#endif // HEIGHTNOISE_H
