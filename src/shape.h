#ifndef SHAPE_H
#define SHAPE_H

#include "shader.h"
//#include "editor.h"

#include <Eigen/Geometry>

/**
 * @brief interface implemented by mesh which contains the needed data for the planet generation
 *
 */


class Shape {
public:

    /**
     * @brief The Vertices struct containing positions normals and colo for each vertex
     *
     */
    struct Vertices{
        std::vector<Eigen::Vector3f> _positions;
        std::vector<Eigen::Vector3f> _normals;
        std::vector<GLfloat> _colors;
    };

    Shape() : _ready(false), _transformation(Eigen::Matrix4f::Identity()) {}
    virtual ~Shape() {}

    /**
     * @brief Creates the _halfEdge attribute from an OBJ file
     *
     * @param filename Path to the file to load
     */
    virtual void load(const std::string& filename) = 0;

    /**
     * @brief Computes all the data needed by OpenGL for the display (_positions,_normals,_colors,_indices)
     *
     */
    virtual void init() = 0;

    /**
     * @brief Displays the data computed init
     *
     * @param shader shader used to display the data
     */
    virtual void display(Shader *shader) = 0;

    /**
     * @brief Saves the planet into a .obj format file, does not include the color yet
     *
     */
    virtual void saveOBJ() = 0;

    /**
     * @brief Saves the planet into a .off format file, does not include the color yet
     *
     */
    virtual void saveOFF() = 0;


    /**
     * @brief Get the Vertices object
     *
     * @return Vertices*
     */
    virtual Vertices* getVertices() = 0;

    /**
     * @brief boundingBox used for the rasterzation
     * @return the boundingBox which contains the vertex of the shape
     */
    const Eigen::AlignedBox3f& boundingBox() const { return _bbox; }

    /**
     * @brief getTransformationMatrix
     * @return
     */
    const Eigen::Affine3f& getTransformationMatrix() const { return _transformation; }

    /**
     * @brief setTransformationMatrix
     * @param changes the _transformation attribute into the transfo parameter
     */

    void setTransformationMatrix(const Eigen::Affine3f& transfo) { _transformation = transfo; }

protected:
    bool _ready;

    /**
     * @brief bounding box used for rasterization
     * 
     */
    Eigen::AlignedBox3f _bbox;

    /**
     * @brief transformation matrix used for the coordinate tranformations
     * 
     */

    Eigen::Affine3f _transformation;

    //Contains the differents points of a face
    // at(v0.idx) to have access of the positions in _vertices._positions.
    std::vector<Eigen::Vector3i> _faces;

    /* List of vertices */
    Vertices* _vertices;



private:

};

#endif // SHAPE_H
