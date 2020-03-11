#include "heightnoise.h"

#include <math.h>
#include <time.h>

using namespace Eigen;

HeightNoise::HeightNoise()
{
    myModule.SetFrequency(0.5+ (std::rand()%1500)/1000.0);
    myModule.SetOctaveCount(4+std::rand()%3);
    myModule.SetPersistence(0.4 + std::rand()%250/1000.0);
}

HeightNoise::~HeightNoise()
{

}

double HeightNoise::getValue(const Vector3f &keygen)
{
    double height = myModule.GetValue(keygen.x(), keygen.y(), keygen.z());
    return std::max(-1.0, std::min(1.0, height));
}
