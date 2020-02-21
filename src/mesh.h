#ifndef MESH_H
#define MESH_H

#include "shape.h"

#include <surface_mesh/surface_mesh.h>
/**
 * @brief Class that contains the needed data for the planet generation
 * 
 */

class Mesh : public Shape
{
public:
    Mesh() {
        _vertices = new Vertices;
    }
    ~Mesh();

    /**
     * @brief Creates the _halfEdge attribute from an OBJ file
     * 
     * @param filename Path to the file to load
     */
    void load(const std::string& filename);

    /**
     * @brief Computes all the data needed by OpenGL for the display (_positions,_normals,_colors,_indices)
     * 
     */
    void init();

    /**
     * @brief Displays the data computed init
     *  
     * @param shader shader used to sisplay the data
     */
    void display(Shader *shader);

    /**
     * @brief 
     * 
     */
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
