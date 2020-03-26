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
 * @param min value
 * @param max value
 * @return a random number. Values between [min, max].
 */
double random(double min, double max);

/**
 * @brief normalRandom
 * @param mean the mean of the normal law
 * @param deviation the deviation of the normal law
 * @return a normal random number that suit to the normal law.
 */
double normalRandom(double mean, double deviation);

//Use for double precision of clamping.
#define CLAMP_EPSILON 10e-6

/**
 * @brief The HeightNoise class generate noise.
 */
class HeightNoise
{

public:

    /**
     * @brief Construct a new Height Noise object
     * 
     * @param seed the seed for aleatory.
     * @param frequence  the frerquence of the noise.
     * @param octave the octave of the noise.
     * @param persistence the persistence of the noise.
     * More informations for parameters in library libnoise.
     */
    HeightNoise(int seed, double frequence, int octave, double persistence);
    ~HeightNoise();

    /**
     * @brief getValue get the value noise.
     * @param keygen Tke key for generation. Same key = same value.
     * @return the value noise in double associated to the key.
     * Domain between [-1, 1]
     */
    double getValue(const Eigen::Vector3f &keygen) const;

private:
    noise::module::Perlin _generator;
    noise::module::Clamp _out;
};

}



#endif // HEIGHTNOISE_H
