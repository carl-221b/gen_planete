#include "rendering_opengl.h"

using namespace Eigen;

Rendering_OpenGL::~Rendering_OpenGL(){

}


void Rendering_OpenGL::initView(){
    glClearColor(0.0f,0.0f,0.0f,0.);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Rendering_OpenGL::initViewPort(int x, int y, int w, int h){
    glViewport(x, y, w, h);
}

void Rendering_OpenGL::initDisplay(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.f, 1.f);
}

void Rendering_OpenGL::polygonModeFill(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void Rendering_OpenGL::polygonModeLine(){
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Rendering_OpenGL::UniformValues(Shader* shader, Trackball cam, Vector3f ligthDir, Matrix3f normal, Matrix4f model){
    glUniformMatrix4fv(shader->getUniformLocation("projection_matrix"), 1, GL_FALSE, cam.computeProjectionMatrix().data());
    glUniform3fv(shader->getUniformLocation("light_dir_world"),1,ligthDir.data());
    glUniformMatrix4fv(shader->getUniformLocation("model_view_matrix"), 1, GL_FALSE, model.data());
    glUniformMatrix3fv(shader->getUniformLocation("normal_matrix"), 1, GL_FALSE, normal.data());
}

void Rendering_OpenGL::checkErrors(){
    checkError();
}


void Rendering_OpenGL::deleteBuffers(){
    glDeleteBuffers(1, &_facesBuffer);
    glDeleteBuffers(2, _vbo);
    glDeleteVertexArrays(1,&_vao);
}

void Rendering_OpenGL::draw(int nb_elements, Shader* shader){

    glBindVertexArray(_vao);

    this->specifyVertexData(shader);

    glDrawElements(GL_TRIANGLES, nb_elements*3,  GL_UNSIGNED_INT, 0);

    glBindVertexArray(0);
}

void Rendering_OpenGL::specifyVertexData(Shader* shader){
    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
    int pos_loc = shader->getAttribLocation("vtx_position");
    glEnableVertexAttribArray(pos_loc);
    glVertexAttribPointer(pos_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), (void*)0);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
    int normal_loc = shader->getAttribLocation("vtx_normal");
    if(normal_loc>=0){
        glEnableVertexAttribArray(normal_loc);
        glVertexAttribPointer(normal_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), (void*)0);
    }

    glBindBuffer(GL_ARRAY_BUFFER, _vbo[2]);
    int color_loc = shader->getAttribLocation("vtx_color");
    if(color_loc>=0)
    {
        glEnableVertexAttribArray(color_loc);
        glVertexAttribPointer(color_loc, 3, GL_FLOAT, GL_FALSE, sizeof(Vector3f), (void*)0);
    }
}

void Rendering_OpenGL::loadBuffer(const Shape::Vertices* vertices, std::vector<Vector3i> faces){
    glGenVertexArrays(1, &_vao);
    glGenBuffers(3, _vbo);

    glBindVertexArray(_vao);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f)*vertices->_positions.size(), vertices->_positions.data(), GL_STATIC_DRAW);

    glBindBuffer(GL_ARRAY_BUFFER, _vbo[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Vector3f)*vertices->_normals.size(), vertices->_normals.data(), GL_STATIC_DRAW);

    //GLuint colorbuffer;
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _vbo[2]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vector4f)*vertices->_colors.size(), vertices->_colors.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &_facesBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _facesBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(Vector3i)*faces.size(), faces.data(),  GL_STATIC_DRAW);

    glBindVertexArray(0);
}
