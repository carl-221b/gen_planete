#include "heightnoise.h"

#include <math.h>
#include <time.h>

using namespace Eigen;

HeightNoise::HeightNoise(int frequence, int octave, int persistence)
{
    myModule.SetFrequency(frequence);
    myModule.SetOctaveCount(octave);
    myModule.SetPersistence(persistence);
}

HeightNoise::~HeightNoise()
{

}

double HeightNoise::getValue(const Vector3f &keygen)
{
    return myModule.GetValue(keygen.x(), keygen.y(), keygen.z());
}
