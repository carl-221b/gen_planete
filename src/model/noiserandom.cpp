#include "noiserandom.h".h"

#include <math.h>
#include <time.h>

using namespace Eigen;
using namespace NoiseRandom;

HeightNoise::HeightNoise(int seed, int frequence, int octave, int persistence)
{
    _generator.SetSeed(seed);
    _generator.SetFrequency(frequence);
    _generator.SetOctaveCount(octave);
    _generator.SetPersistence(persistence);

    _out.SetSourceModule(0, _generator);
    _out.SetBounds(-1 + CLAMP_EPSILON, 1 - CLAMP_EPSILON);
}

HeightNoise::~HeightNoise()
{

}

double HeightNoise::getValue(const Vector3f &keygen)
{
    return _out.GetValue(keygen.x(), keygen.y(), keygen.z());
}


static std::random_device _randomDevice;
static std::mt19937 _randomGen(_randomDevice());

double NoiseRandom::normalRandom(double mean, double deviation)
{
    std::normal_distribution<double> distribution(mean, deviation);
    return distribution(_randomGen);
}

double NoiseRandom::random()
{
    return 2*( (double)(std::rand()) + 1. )/( (double)(RAND_MAX) + 1. ) - 1;
}
