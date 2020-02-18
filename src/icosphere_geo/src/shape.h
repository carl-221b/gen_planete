#ifndef SHAPE_H
#define SHAPE_H

#include "shader.h"
#include "editor.h"

#include <Eigen/Geometry>

class Shape {
public:
    Shape() : _ready(false), _transformation(Eigen::Matrix4f::Identity()) {}
    virtual ~Shape() {}

    virtual void load(const std::string& filename) = 0;
    virtual void init() = 0;
    virtual void display(Shader *shader) = 0;
    virtual void edit(Editor *edit) = 0;


    const Eigen::AlignedBox3f& boundingBox() const { return _bbox; }
    const Eigen::Affine3f& getTransformationMatrix() const { return _transformation; }
    void setTransformationMatrix(const Eigen::Affine3f& transfo) { _transformation = transfo; }

protected:
    bool _ready;
    Eigen::AlignedBox3f _bbox;
    Eigen::Affine3f _transformation;

private:

};

#endif // SHAPE_H
