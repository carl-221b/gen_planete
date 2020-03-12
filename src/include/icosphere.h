#ifndef MESH_H
#define MESH_H

#include "shape.h"
#include "rendering.h"

#include <surface_mesh/surface_mesh.h>

#define DEFAULT_NB_SUBDIVISION 8

/**
 * @brief Class that contains the needed data for the planet generation
 * 
 */

class Icosphere : public Shape
{
public:
    Icosphere(int nbSubdivision);
    ~Icosphere();

    /**
     * @brief Creates the _halfEdge attribute from an OBJ file
     * 
     * @param filename Path to the file to load
     */
    void load(const std::string& filename);

    /**
     * @brief Subdivides the triangluar mesh. Each triangle is subdivided into 4 smaller triangles which allow the mesh to look smoother
     *
     * The algorithm  is from : https://www.labri.fr/perso/pbenard/teaching/mondes3d/td9.html
     * which is based on the thesis : https://www.microsoft.com/en-us/research/wp-content/uploads/2016/02/thesis-10.pdf
     *
     * Step 1 : after defining a new Surface_mesh, it inserts the vertices of the old one.
     *          Then, it adds the intermediate vertices (Ui) on the edges of each triangles :
     *
     *                              V1- - -U5- - V3
     *                             /  \         /
     *                            /    \       /
     *                           U2     U1    U3
     *                          /        \   /
     *                         /          \ /
     *                       V0- - -U4- - -V2
     *
     *        with the formula : U1 = (3/8)*V0+(3/8)*V2+(1/8)*V1+(1/8)*V3  (see above links)
     *
     *Step 2 : it adds the 4 new sub triangles to the new Surface_mesh
     *
     *                              V1
     *                             /  \
     *                            /    \
     *                           U0- - -U1
     *                          /  \   / \
     *                         /    \ /   \
     *                       V0- - -U2- - -V2
     *
     * Step 3 : it computes the new positions of the initial vertices :
     *
     *                                      di
     *          Vi' = (1 - B*di) * Vi + B * ∑(Vij)   (see above links)
     *                                     j=1
     *
     * Step 4 : it replaces the old Surface_mesh by the new one, and updates the attributes of the mesh from it
     */
    void subdivide();

    /**
     * @brief Saves the planet into a .obj format file, does not include the color yet
     *
     */
    void saveOBJ(const std::string& filename);
    
    /**
     * @brief Saves the planet into a .off format file, does not include the color yet
     * 
     */
    void saveOFF(const std::string& filename);

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

private:

    /**
     * @brief Updates mesh's attributes (vertices and faces) from its Surface_mesh
     */
    void updateMeshFromSurfaceMesh();

    /**
     * @brief _halfEdge : structure used to know the connectivity between the different faces and vertices.
     */
    surface_mesh::Surface_mesh _halfEdge;

protected:

};


#endif // MESH_H
