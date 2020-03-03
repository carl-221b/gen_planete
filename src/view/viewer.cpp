#include "viewer.h"

using namespace Eigen;

Viewer::Viewer(Rendering* rendering)
{
   _rendering = rendering;
}

Viewer::~Viewer()
{
    delete _simple_shader;
    delete _line_shader;
}

////////////////////////////////////////////////////////////////////////////////
// GL stuff

// initialize OpenGL context
void Viewer::init(int w, int h, Shape* shape){
    _winWidth = w;
    _winHeight = h;

    _rendering->initViewPort(0,0,w,h);

    _ligthDir = Vector3f(-1,1,1).normalized();

    _simple_shader = new Shader();
    _line_shader = new Shader();

    _shape = shape;

    loadPrograms();

    _cam.setSceneCenter(_shape->boundingBox().center());
    _cam.setSceneRadius(_shape->boundingBox().sizes().maxCoeff());
    _cam.setSceneDistance(_cam.sceneRadius() * 3.f);
    _cam.setMinNear(0.01f);
    _cam.setNearFarOffsets(-_cam.sceneRadius() * 100.f,
                            _cam.sceneRadius() * 100.f);
    _cam.setScreenViewport(AlignedBox2f(Vector2f(0.0,0.0), Vector2f(w,h)));

    _rendering->initView();
}

void Viewer::reshape(int w, int h){
    _winWidth = w;
    _winHeight = h;
    _rendering->initViewPort(0,0,w,h);
    _cam.setScreenViewport(AlignedBox2f(Vector2f(0.0,0.0), Vector2f(w,h)));
}


/*!
   callback to draw graphic primitives
   you may edit it if you want to change de drawing procedure (add new objects
   for example).
 */
void Viewer::display()
{
    _rendering->initDisplay();

    Matrix4f view_matrix = _cam.computeViewMatrix();
    Matrix4f model_view = (view_matrix*_shape->getTransformationMatrix()).matrix();
    Matrix3f normal_matrix = (view_matrix*_shape->getTransformationMatrix()).linear().inverse().transpose();

    _rendering->polygonModeFill();

    _simple_shader->activate();

    _rendering->UniformValues(_simple_shader, _cam, _ligthDir, normal_matrix, model_view);

    _shape->draw(_simple_shader);

    _simple_shader->deactivate();

    if(_wireframe){
        _rendering->polygonModeLine();
        _line_shader->activate();

        _rendering->UniformValues(_line_shader, _cam, _ligthDir, normal_matrix, model_view);

        _shape->draw(_line_shader);

    }

    _line_shader->deactivate();
    _rendering->checkErrors();
}


void Viewer::updateScene() 
{
    display();
}

void Viewer::loadPrograms()
{
    _simple_shader->loadFromFiles(DATA_DIR"/shaders/simple.vert",DATA_DIR"/shaders/simple.frag");
    _line_shader->loadFromFiles(DATA_DIR"/shaders/line.vert",DATA_DIR"/shaders/simple.frag");
}

////////////////////////////////////////////////////////////////////////////////
// Events

/*!
   callback to manage mouse : called when user press or release mouse button
   You can change in this function the way the user
   interact with the system.
 */
void Viewer::mousePressed(GLFWwindow *window, int button, int action)
{
    if(action == GLFW_PRESS) {
        if(button == GLFW_MOUSE_BUTTON_LEFT)
        {
            std::cout << "Debug: " << "myQuaternion.vec() = " << _cam.sceneOrientation().vec() << std::endl;
            _cam.startRotation(_lastMousePos);
        }
        else if(button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            //_cam.startTranslation(_lastMousePos);
        }
        _button = button;
    }
    else if(action == GLFW_RELEASE) {
        if(_button == GLFW_MOUSE_BUTTON_LEFT)
        {
            std::cout << "Debug: " << "myQuaternion camera vec value = " << _cam.sceneOrientation().vec() << std::endl;
            _cam.endRotation();
        }
        else if(_button == GLFW_MOUSE_BUTTON_RIGHT)
        {
            //_cam.endTranslation();
        }
        _button = -1;
    }
}


/*!
   callback to manage mouse : called when user move mouse with button pressed
   You can change in this function the way the user
   interact with the system.
 */
void Viewer::mouseMoved(int x, int y)
{
    if(_button == GLFW_MOUSE_BUTTON_LEFT)
    {
        _cam.dragRotate(Vector2f(x,y));
    }
    else if(_button == GLFW_MOUSE_BUTTON_RIGHT)
    {
        _cam.dragTranslate(Vector2f(x,y));
    }
    _lastMousePos = Vector2f(x,y);
}

void Viewer::mouseScroll(double x, double y)
{

    //std::cout << "Debug: " << "myQuaternion camera vec value = " << _cam.sceneOrientation().vec() << std::endl;
    if(_cam.sceneDistance() > 0.9 && _cam.sceneDistance() < 5.7){
        //std::cout << "Debug" << "Value of y for the mouse = " << y << std::endl;
        if(y > 0)
            _cam.zoom(1.1);
        else
            _cam.zoom(1.0/1.1);
     }else if(_cam.sceneDistance() > 5.7){
        if(y > 0)
            _cam.zoom(1.1);
     }else{
        if(y < 0)
            _cam.zoom(1.0/1.1);
     }
}


/*!
   callback to manage keyboard interactions
   You can change in this function the way the user 
   interact with the system.
 */
void Viewer::keyPressed(int key, int action, int mods)
{
    if(action == GLFW_PRESS) {
        if (key == GLFW_KEY_R)
            loadPrograms();
        else if(key == GLFW_KEY_S){
            _shape->saveOBJ("planet");
        }
        else if(key == GLFW_KEY_W)
        {
            _wireframe = !_wireframe;
        }
    }
}

void Viewer::charPressed(int key)
{
}
