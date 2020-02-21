#ifndef HEIGHTNOISE_H
#define HEIGHTNOISE_H

#include <Eigen/Geometry>

class HeightNoise
{
public:
    HeightNoise();
    ~HeightNoise();

    float getValue(const Eigen::Vector3f &keygen);
};

#endif // HEIGHTNOISE_H
