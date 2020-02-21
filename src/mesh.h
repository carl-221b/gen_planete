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
     * @param shader shader used to display the data
     */
    void display(Shader *shader);

    void subdivide();

    /**
     * @brief Saves the planet into a .obj format file, does not include the color yet
     * 
     */
    void saveOBJ();
    
    /**
     * @brief Saves the planet into a .off format file, does not include the color yet
     * 
     */
    void saveOFF();

    /**
     * @brief Get the Vertices object
     * 
     * @return Vertices*
     */
    Vertices* getVertices();
    

    /**
     * @brief Get the number of faces
     * 
     * @return int the number of faces
     */
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
