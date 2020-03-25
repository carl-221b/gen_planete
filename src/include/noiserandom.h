#ifndef HEIGHTNOISE_H
#define HEIGHTNOISE_H

#include <Eigen/Geometry>
#include <random>
#include <noise/noise.h>

/**
 *  Namespace for handle all random number and noise generation.
 */
namespace NoiseRandom
{

/**
 * @brief random
 * @return a random number. Value between [-1, 1].
 */
double random(double min, double max);

/**
 * @brief normalRandom
 * @param mean the mean of the normal law
 * @param deviation the deviation of the norma law
 * @return a normal random number that suit to the normal law.
 */
double normalRandom(double mean, double deviation);


#define CLAMP_EPSILON 10e-6

/**
 * @brief The HeightNoise class generate noise.
 */
class HeightNoise
{

public:

    HeightNoise(int seed, double frequence, int octave, double persistence);
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
