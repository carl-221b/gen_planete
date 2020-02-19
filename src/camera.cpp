#include "camera.h"

using namespace Eigen;

Matrix4f Camera::perspective(float fovy, float aspect, float zNear, float zFar)
{
    float tanHalfFovy = tan(fovy / 2.f);

    Matrix4f m;
    m << 1.f / (aspect * tanHalfFovy), 0,  0, 0,
             0,      1.f / (tanHalfFovy),  0, 0,
             0, 0, - (zFar + zNear) / (zFar - zNear), - (2.f * zFar * zNear) / (zFar - zNear),
             0,     0,       -1,          0;
    return m;
}

Matrix4f Camera::lookAt(const Vector3f& position, const Vector3f& target, const Vector3f& up)
{
    Matrix3f L;
    L.row(2) = (position - target).normalized();
    L.row(0) = up.cross(L.row(2)).normalized();
    L.row(1) = L.row(2).cross(L.row(0)).normalized();

    Matrix4f m(Matrix4f::Identity());
    m.block<3,3>(0, 0) = L;
    m.block<3,1>(0, 3) = L * (-position);
    return m;
}
