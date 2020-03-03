#ifndef RENDERING_H
#define RENDERING_H

#include "shader.h"
#include "trackball.h"
#include "shape.h"

#include <Eigen/Geometry>

/**
 * @brief Interface of Bridge pattern use to block the dependance with library like openGL.
 */

class Rendering {
public:
    Rendering(){}
    virtual ~Rendering(){}

    virtual void initView() = 0;
    virtual void initViewPort(int x, int y, int w, int h) = 0;
    virtual void initDisplay() = 0;
    virtual void polygonModeFill() = 0;
    virtual void polygonModeLine() = 0;
    virtual void UniformValues(Shader* shader, Trackball cam, Eigen::Vector3f lightDir, Eigen::Matrix3f normal, Eigen::Matrix4f model) = 0;
    virtual void checkErrors() = 0;

    virtual void draw(int nb_elements, Shader* shader) = 0;
    virtual void specifyVertexData(Shader* shader) = 0;
    virtual void loadBuffer(Shape::Vertices* vertices, std::vector<Eigen::Vector3i>) = 0;



};

#endif // RENDERING_H
