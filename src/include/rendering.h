#ifndef RENDERING_H
#define RENDERING_H

#include "shader.h"
#include "trackball.h"
#include "shape.h"

#include <Eigen/Geometry>

/**
 * @brief Interface of Bridge pattern use to block the dependance with library like openGL.
 */

class Rendering {
public:
    Rendering(){}
    virtual ~Rendering(){}

    /**
     * @brief initialize View
     */
    virtual void initView() = 0;

    /**
     * @brief initialize Viewport
     * @param x : abscissa of origin point
     * @param y : ordinate of origin point
     * @param w : width of the window
     * @param h : height of the window
     */
    virtual void initViewPort(int x, int y, int w, int h) = 0;

    /**
     * @brief initialize Display
     */
    virtual void initDisplay() = 0;

    /**
     * @brief Switch to polygone mode fill
     */
    virtual void polygonModeFill() = 0;

    /**
     * @brief Switch to polygone mode line
     */
    virtual void polygonModeLine() = 0;

    /**
     * @brief Uniform values for renderer
     * @param shader : shader used to draws the data
     * @param cam : camera used for the scene
     * @param lightDir : light's direction
     * @param normal : normal's transformation matrix
     * @param model : model's transformation matrix
     */
    virtual void UniformValues(Shader* shader, Trackball cam, Eigen::Vector3f lightDir, Eigen::Matrix3f normal, Eigen::Matrix4f model, int sea_mode) = 0;

    /**
     * @brief check errors
     */
    virtual void checkErrors() = 0;

    /**
     * @brief delete buffers
     */
    virtual void deleteBuffers() = 0;

    /**
     * @brief Draws the data computed init
     * @param nb_elements : number of elements (faces) to draw
     * @param shader : shader used to draws the data
     */
    virtual void draw(int nb_elements, Shader* shader) = 0;

    /**
     * @brief Sends vertices data to the shader
     * @param shader : shader used to display the data
     */
    virtual void specifyVertexData(Shader* shader) = 0;

    /**
     * @brief Computes all the data needed by OpenGL for the display (_positions,_normals,_colors,_indices)
     * @param vertices : vertices of the shape
     * @param faces : faces of the shape
     */
    virtual void loadBuffer(const Shape::Vertices* vertices, std::vector<Eigen::Vector3i> faces) = 0;



};

#endif // RENDERING_H
