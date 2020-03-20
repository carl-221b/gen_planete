#include "heightnoise.h"

#include <math.h>
#include <time.h>

using namespace Eigen;

HeightNoise::HeightNoise(/*int seed,*/ int frequence, int octave, int persistence)
{
    //myModule.SetSeed(seed);
    myModule.SetFrequency(6);
    myModule.SetOctaveCount(1.0);
    myModule.SetPersistence(0.5);
}

HeightNoise::~HeightNoise()
{

}

double HeightNoise::getValue(const Vector3f &keygen)
{
    return myModule.GetValue(keygen.x(), keygen.y(), keygen.z());
}
