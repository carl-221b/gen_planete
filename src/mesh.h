#ifndef MESH_H
#define MESH_H

#include "shape.h"

#include <surface_mesh/surface_mesh.h>

class Mesh : public Shape
{
public:
    Mesh() {
        _vertices = new Vertices;
    }
    ~Mesh();

    void load(const std::string& filename);
    void init();
    void display(Shader *shader);
    void subdivide();

    void saveOBJ();
    void saveOFF();
    Vertices* getVertices();
    void updateVertices(Vertices* vertices);


    int numFaces() const { return _halfEdge.faces_size(); }
    /// Copy vertex attributes from the CPU to GPU memory (needs to be called after editing any vertex attributes: positions, normals, texcoords, masks, etc.)
    void updateVBO();

private:
    void updateMeshFromSurfaceMesh();
    void specifyVertexData(Shader *shader);


    surface_mesh::Surface_mesh _halfEdge;

    GLuint _facesBuffer;

    GLuint _vao;
    GLuint _vbo[3]; // positions, normals, colors

protected:

};


#endif // MESH_H
