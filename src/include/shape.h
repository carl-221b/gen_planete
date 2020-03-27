#ifndef SHAPE_H
#define SHAPE_H

#include "shader.h"

#include <Eigen/Geometry>

/**
 * @brief interface which contains the needed data for the planet generation.
 */
class Shape {
public:

    /**
     * @brief The Vertices struct containing positions normals and colors for each vertex.
     */
    struct Vertices{
        std::vector<Eigen::Vector3f> _positions;
        std::vector<Eigen::Vector3f> _normals;
        std::vector<Eigen::Vector3f> _colors;
    };

    Shape() : _transformation(Eigen::Matrix4f::Identity()) {}
    virtual ~Shape() = default;

    /**
     * @brief Creates the _halfEdge attribute from an OBJ file
     *
     * @param filename Path to the file to load
     */
    virtual void load(const std::string& filename) = 0;

    /**
     * @brief Get the number of faces
     * 
     * @return unsigned int the number of faces
     */ 
    unsigned int numFaces() const { return _faces.size(); }

    /**
     * @brief Get the Vertices object (editable)
     *
     * @return Vertices*
     */
    Vertices* getVertices() {return _vertices;}

    /**
     * @brief Get the Vertices object (const)
     *
     * @return const Vertices*
     */
    const Vertices* getVertices() const {return _vertices;}

    /**
     * @brief Compute normal for each face.
     */
    virtual void computeNormals() = 0;

    /**
     * @brief boundingBox used for the rasterzation
     * @return the boundingBox which contains the vertex of the shape
     */
    const Eigen::AlignedBox3f& boundingBox() const { return _bbox; }

    /**
     * @brief getTransformationMatrix
     * @return a transformation matrix
     */
    const Eigen::Affine3f& getTransformationMatrix() const { return _transformation; }

    /**
     * @brief setTransformationMatrix
     * @param changes the _transformation attribute into the transfo parameter
     */
    void setTransformationMatrix(const Eigen::Affine3f& transfo) { _transformation = transfo; }

    /**
     * @brief getFaces
     * @return a vector of the faces used on the shape
     */
    const std::vector<Eigen::Vector3i> getFaces() const { return _faces; }

protected:

    /**
     * @brief bounding box used for rasterization
     */
    Eigen::AlignedBox3f _bbox;

    /**
     * @brief transformation matrix used for the coordinate tranformations
     */
    Eigen::Affine3f _transformation;

    //Contains the differents points of a face
    // at(v0.idx) to have access of the positions in _vertices._positions.
    std::vector<Eigen::Vector3i> _faces;

    /* List of vertices */
    Vertices* _vertices;

};

#endif // SHAPE_H
