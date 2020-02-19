#ifndef EDITOR_H
#define EDITOR_H

#include <Eigen/Geometry>
#include <surface_mesh/surface_mesh.h>

class Editor {
public:
    Editor() {}
    virtual ~Editor() {}
    virtual surface_mesh::Surface_mesh modifyShape(surface_mesh::Surface_mesh surface_mesh) = 0;

};

#endif // EDITOR_H
