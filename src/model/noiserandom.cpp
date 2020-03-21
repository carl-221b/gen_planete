#include "noiserandom.h"

#include <math.h>
#include <time.h>

static std::random_device _randomDevice;
static std::mt19937 _randomGen(_randomDevice());

double NoiseRandom::normalRandom(double mean, double deviation)
{
    std::normal_distribution<double> distribution(mean, deviation);
    return distribution(_randomGen);
}

double NoiseRandom::random(double min, double max)
{
    std::uniform_real_distribution<double>distribution(min, max);
    return distribution(_randomGen);
}

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
