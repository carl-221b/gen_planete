#ifndef MESH_H
#define MESH_H

#include "shape.h"

#include <surface_mesh/surface_mesh.h>

class Mesh : public Shape
{
public:
    Mesh() {}
    ~Mesh();
    void load(const std::string& filename);
    void init();
    void display(Shader *shader);
    void edit(Editor *edit);

    int numFaces() { return _halfEdge.faces_size(); }
    /// Copy vertex attributes from the CPU to GPU memory (needs to be called after editing any vertex attributes: positions, normals, texcoords, masks, etc.)
    void updateVBO();


private:
    void load();
    void specifyVertexData(Shader *shader);
    void subdivide();


    std::vector<Eigen::Vector3i> _indices;

    surface_mesh::Surface_mesh _halfEdge;

    std::vector<Eigen::Vector3f> _positions;
    std::vector<Eigen::Vector3f> _normals;

    GLuint _indicesBuffer;

    GLuint _vao;
    GLuint _vbo[2]; // positions, normals
};


#endif // MESH_H
