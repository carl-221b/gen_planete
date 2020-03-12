#ifndef VIEWER_H
#define VIEWER_H

#include <iostream>

#include "shader.h"
#include "icosphere.h"
#include "trackball.h"
#include "rendering.h"

#include "basic_editor.h"

/**
 * @brief 
 * 
 */
class Viewer
{
public:
    //! Constructor
    Viewer(Rendering* rendering);
    virtual ~Viewer();

    //gl interaction

    /**
     * @brief creates a new window to display shape onto
     * 
     * @param w width of the window
     * @param h height of the window
     * @param shape shape object to be displayed
     */
    void init(int w, int h, Shape* shape);

    /**
     * @brief draw on the window
     * 
     */
    void display();

    /**
     * @brief refresh the window if called
     * 
     */
    void updateScene();

    /**
     * @brief reshape window
     * 
     * @param w width of the reshaped window
     * @param h height of the reshaped window
     */
    void reshape(int w, int h);

    /**
     * @brief loads all the shader needed for the display
     * 
     */
    void loadPrograms();

    // Used to handle mouse interaction with the window
    void mousePressed(GLFWwindow* window, int button, int action);
    void mouseMoved(int x, int y);
    void mouseScroll(double x, double y);
    
    // Used to handle key interaction with the window
    void keyPressed(int key, int action, int mods);
    void charPressed(int key);

private:
    Trackball _cam;

    int _winWidth, _winHeight;

    Shader* _simple_shader;
    Shader* _line_shader;
    Shape* _shape;

    bool _wireframe = false;

    Eigen::Vector3f _lightDir;

    // Mouse parameters
    Eigen::Vector2f _lastMousePos;
    int _button = -1;

    //Render
    Rendering* _rendering;
    bool _ready = false;
};

#endif
