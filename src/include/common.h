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

    Timer() = default;

    /**
    * @brief Permit to update the start time of the timer. Call it on firts use and to reset timer.
    */
    void startTimer(){  _start = Clock::now(); }
    /**
    * @brief Permit to update the end time of the timer. Don't neccesarly need to be called with startTimer() if you want cumulative time.
    */
    void endTimer(){  _end = Clock::now(); }

    /**
    * @brief Get the duaration beetween the last startTimer and endTimer. If this funtions haven't be called, unpredictable behaviour.
    */
    double getDurationMs() const
    {
        return std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();
    }

private :

    std::chrono::time_point<Clock> _start, _end;
};

/**
 * @brief cartesianToPolarCoord, transform cartesian coordinates to spherical.
 * Conventions : 
 *      Cartesian coordinates in input,
 *      Spherical coordinates to ouput, use radians with rho in [0, infinity), theta in [0, PI], phi in [0, 2 * PI).
 * @param cartesian coordinates to transform.
 * @return Vector3f with rho, theta, phi in this order.
 */
static Eigen::Vector3f cartesianToSphericalCoord(const Eigen::Vector3f& cartesian)
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
 * Convention : 
 *      Spherical coordinates to input, use radians with rho in [0, infinity), theta in [0, PI], phi in [0, 2 * PI),
 *      Cartesians coordinates to ouytput with origin at the center of sphere.
 * @param polar coordinates to transform.
 * @return the cartesian coordinates x, y , z.
 */
static Eigen::Vector3f sphericalToCartesianCoord(const Eigen::Vector3f& polar)
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
