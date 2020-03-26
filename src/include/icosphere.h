#ifndef MESH_H
#define MESH_H

#include "shape.h"
#include "rendering.h"

#include <surface_mesh/surface_mesh.h>
#include "noiserandom.h"

#define DEFAULT_NB_SUBDIVISION 8

/**
 * @brief Implementation of Shape interface.
 */
class Icosphere : public Shape
{
public:

    /**
     * @brief Construct a new Icosphere object
     * 
     * @param nbSubdivision the number of subdivision. Higher it is, higher number of polygons it have.
     * Don't use it higher than 10 because of performances issues.
     * @param organicLook permit to displace vertices for a more organic mesh.
     */
    Icosphere(unsigned int nbSubdivision, bool organicLook = false);
    ~Icosphere();

    /**
     * @brief Creates the _halfEdge attribute from an OBJ file
     * 
     * @param filename Path to the file to load
     */
    virtual void load(const std::string& filename) override;

    /**
     * @brief Updates mesh's attributes (vertices and faces) from its Surface_mesh
     */
    void updateMeshFromSurfaceMesh();

    /**
     * @brief Compute normal for each face
     */
    virtual void computeNormals() override;

    /**
     * @brief Move vertices positions to make the planet look more organic
     */
    void organicTriangulation();
    
private:

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
     * @brief _halfEdge : structure used to know the connectivity between the different faces and vertices.
     */
    surface_mesh::Surface_mesh _halfEdge;
};


#endif // MESH_H
