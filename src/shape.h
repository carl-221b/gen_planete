#ifndef SHAPE_H
#define SHAPE_H

#include "shader.h"
//#include "editor.h"

#include <Eigen/Geometry>

class Shape {
public:
    struct Vertices{
        std::vector<Eigen::Vector3f> _positions;
        std::vector<Eigen::Vector3f> _normals;
        std::vector<GLfloat> _colors;
    };

    Shape() : _ready(false), _transformation(Eigen::Matrix4f::Identity()) {}
    virtual ~Shape() {}

    virtual void load(const std::string& filename) = 0;
    virtual void init() = 0;
    virtual void display(Shader *shader) = 0;
    virtual void subdivide() = 0;

    virtual void saveOBJ() = 0;
    virtual void saveOFF() = 0;
    virtual Vertices* getVertices() = 0;


    const Eigen::AlignedBox3f& boundingBox() const { return _bbox; }
    const Eigen::Affine3f& getTransformationMatrix() const { return _transformation; }
    void setTransformationMatrix(const Eigen::Affine3f& transfo) { _transformation = transfo; }

protected:
    bool _ready;
    Eigen::AlignedBox3f _bbox;
    Eigen::Affine3f _transformation;

    //Contains the differents points of a face
    // at(v0.idx) to have access of the positions in _vertices._positions.
    std::vector<Eigen::Vector3i> _faces;

    /* List of vertices */
    Vertices* _vertices;

public:
    virtual void updateVertices(Vertices* vertices) = 0;

private:

};

#endif // SHAPE_H
