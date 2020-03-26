#ifndef CAMERA_H
#define CAMERA_H

#include "trackball.h"

/**
 * @brief Implementation of Trackball class. 
 */
class Camera : public Trackball
{
public:
    Camera() = default;

    static Eigen::Matrix4f perspective(float fovy, float aspect, float zNear, float zFar);
    static Eigen::Matrix4f lookAt(const Eigen::Vector3f& position, const Eigen::Vector3f& target, const Eigen::Vector3f& up);
};

#endif // CAMERA_H
