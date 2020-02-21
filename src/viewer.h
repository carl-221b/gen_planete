#ifndef VIEWER_H
#define VIEWER_H

#include "opengl.h"

#include <iostream>

#include "shader.h"
#include "mesh.h"
#include "trackball.h"

#include "basic_editor.h"

class Viewer
{
public:
    //! Constructor
    Viewer();
    virtual ~Viewer();

    // gl stuff
    void init(int w, int h, Shape* shape);
    void display();
    void updateScene();
    void reshape(int w, int h);
    void loadPrograms();

    // events
    void mousePressed(GLFWwindow* window, int button, int action);
    void mouseMoved(int x, int y);
    void mouseScroll(double x, double y);
    void keyPressed(int key, int action, int mods);
    void charPressed(int key);

private:
    Trackball _cam;

    int _winWidth, _winHeight;

    Shader* _simple_shader;
    Shader* _line_shader;
    Shape* _shape;

    bool _wireframe = false;

    Eigen::Vector3f _ligthDir;

    // Mouse parameters
    Eigen::Vector2f _lastMousePos;
    int _button = -1;
};

#endif
