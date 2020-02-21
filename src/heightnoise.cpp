#include "heightnoise.h"

#include <noise/noise.h>

using namespace noise;
using namespace Eigen;

HeightNoise::HeightNoise()
{

}

HeightNoise::~HeightNoise()
{

}

float HeightNoise::getValue(const Vector3f &keygen)
{
    module::Perlin myModule;
    myModule.SetFrequency(1.f);
    double height = myModule.GetValue(keygen.x(), keygen.y(), keygen.z());
    return height;
}
