#ifndef NOISEGENERATOR_H
#define NOISEGENERATOR_H

#include "noisemap.h"

template <typename T>
class NoiseGenerator
{
public:
    NoiseGenerator();
    NoiseMap<T> createNoise();
};

#endif // NOISEGENERATOR_H
