#ifndef COMMON_H
#define COMMON_H

#include <iostream>

#include <Eigen/Geometry>
#include <math.h>

#include <chrono>

/**
 * @brief The Timer class, used for durationn in Ms.
 */
class Timer
{
    typedef std::chrono::high_resolution_clock Clock;
public:

    Timer()
    {}

    void startTimer(){  _start = Clock::now(); }
    void endTimer(){  _end = Clock::now(); }
    double getDurationMs()
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();
    }

private :

    std::chrono::time_point<Clock> _start, _end;
};

/**
 * @brief cartesianToPolarCoord, transform cartesian coordinates to polar.
 * Convention : use radians to output.
 * @param cartesian coordinates
 * @return Vector3f with rho, theta, phi in this order.
 */
static Eigen::Vector3f cartesianToPolarCoord(const Eigen::Vector3f& cartesian)
{
    float rho = cartesian.norm();
    if(rho == 0)
    {
        throw std::runtime_error("Norm cartesian coordinate equal to zero.\n");
    }
    float theta = std::acos(cartesian.z()/rho);
    float phi = std::atan2(cartesian.y(), cartesian.x());

    return Eigen::Vector3f(rho,theta,phi);
}

/**
 * @brief polarToCartesianCoord, transform cartesian coordinates to polar.
 * Convention : use origin to center of sphere to output.
 * @param polar coordinates
 * @return the cartesian coordinates x, y , z.
 */
static Eigen::Vector3f polarToCartesianCoord(const Eigen::Vector3f& polar)
{
    float r = polar.x();
    if(r == 0)
    {
        throw std::runtime_error("Rho polar coordinate equal to zero.\n");
    }

    float x = r * std::sin(polar.y()) * std::cos(polar.z());
    float y = r * std::sin(polar.y()) * std::sin(polar.z());
    float z = r * std::cos(polar.y());

    return Eigen::Vector3f(x,y,z);
}

#endif
