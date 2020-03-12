#ifndef RENDERING_OPENGL_H
#define RENDERING_OPENGL_H


#include "shader.h"
#include "rendering.h"
#include "shape.h"
#include "opengl.h"

#include <Eigen/Geometry>


class Rendering_OpenGL : public Rendering
{
public:
    //Constructor
    Rendering_OpenGL(): Rendering(){}
    ~Rendering_OpenGL();


    void initView();
    void initViewPort(int x, int y, int w, int h);
    void initDisplay();
    void polygonModeLine();
    void polygonModeFill();
    void UniformValues(Shader* shader, Trackball cam, Eigen::Vector3f lightDir, Eigen::Matrix3f normal, Eigen::Matrix4f model);
    void checkErrors();


    void deleteBuffers();
    void draw(int nb_elements, Shader* shader);
    void specifyVertexData(Shader* shader);
    void loadBuffer(Shape::Vertices* vertices, std::vector<Eigen::Vector3i> faces);

private:
    /**
     * @brief Variables used for openGL buffers
     */
    GLuint _facesBuffer;
    GLuint _vao;
    GLuint _vbo[3]; // positions, normals, colors
};

#endif // RENDERING_OPENGL_H
