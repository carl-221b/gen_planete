#include "viewer.h"

using namespace Eigen;

Viewer::Viewer()
{
}

Viewer::~Viewer()
{
    delete _simple_shader;
    delete _blinn_shader;
    delete _mesh;
}

////////////////////////////////////////////////////////////////////////////////
// GL stuff

// initialize OpenGL context
void Viewer::init(int w, int h){
    _winWidth = w;
    _winHeight = h;
    glViewport(0, 0, w, h);

    _ligthDir = Vector3f(-1,1,1).normalized();

    _simple_shader = new Shader();
    _blinn_shader = new Shader();

    loadPrograms();

    //Mesh
    _mesh = new Mesh();
    _mesh->load(DATA_DIR"/models/icosa.obj");
    _mesh->init();

    //Editor* basic_editor = new Basic_Editor();
    //_mesh->edit(basic_editor);

    _cam.setSceneCenter(_mesh->boundingBox().center());
    _cam.setSceneRadius(_mesh->boundingBox().sizes().maxCoeff());
    _cam.setSceneDistance(_cam.sceneRadius() * 3.f);
    _cam.setMinNear(0.01f);
    _cam.setNearFarOffsets(-_cam.sceneRadius() * 100.f,
                            _cam.sceneRadius() * 100.f);
    _cam.setScreenViewport(AlignedBox2f(Vector2f(0.0,0.0), Vector2f(w,h)));

    glClearColor(0.3f,0.3f,0.3f,0.);

    glEnable(GL_DEPTH_TEST);
    glDisable(GL_CULL_FACE);
    glCullFace(GL_BACK);
}

void Viewer::reshape(int w, int h){
    _winWidth = w;
    _winHeight = h;
    glViewport(0, 0, w, h);
    _cam.setScreenViewport(AlignedBox2f(Vector2f(0.0,0.0), Vector2f(w,h)));
}


/*!
   callback to draw graphic primitives
   you may edit it if you want to change de drawing procedure (add new objects
   for example).
 */
void Viewer::display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glEnable(GL_POLYGON_OFFSET_FILL);
    glPolygonOffset(1.f, 1.f);

    _blinn_shader->activate();

    glUniformMatrix4fv(_blinn_shader->getUniformLocation("projection_matrix"), 1, GL_FALSE, _cam.computeProjectionMatrix().data());
    glUniform3fv(_blinn_shader->getUniformLocation("light_dir_world"),1,_ligthDir.data());

    Matrix4f view_matrix = _cam.computeViewMatrix();
    Matrix4f model_view = (view_matrix*_mesh->getTransformationMatrix()).matrix();
    glUniformMatrix4fv(_blinn_shader->getUniformLocation("model_view_matrix"), 1, GL_FALSE, model_view.data());
    Matrix3f normal_matrix = (view_matrix*_mesh->getTransformationMatrix()).linear().inverse().transpose();
    glUniformMatrix3fv(_blinn_shader->getUniformLocation("normal_matrix"), 1, GL_FALSE, normal_matrix.data());

    _mesh->display(_blinn_shader);

    _blinn_shader->deactivate();

    if(_wireframe) {
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        _simple_shader->activate();

        glUniformMatrix4fv(_simple_shader->getUniformLocation("projection_matrix"), 1, GL_FALSE, _cam.computeProjectionMatrix().data());
        glUniform3fv(_simple_shader->getUniformLocation("light_dir_world"),1,_ligthDir.data());
        glUniformMatrix4fv(_simple_shader->getUniformLocation("model_view_matrix"), 1, GL_FALSE, model_view.data());
        glUniformMatrix3fv(_simple_shader->getUniformLocation("normal_matrix"), 1, GL_FALSE, normal_matrix.data());

        _mesh->display(_simple_shader);

        _simple_shader->deactivate();
    }
    checkError();
}


void Viewer::updateScene() 
{
    display();
}

void Viewer::loadPrograms()
{
    _simple_shader->loadFromFiles(DATA_DIR"/shaders/simple.vert",DATA_DIR"/shaders/simple.frag");
    _blinn_shader->loadFromFiles(DATA_DIR"/shaders/blinn.vert",DATA_DIR"/shaders/blinn.frag");
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
            _cam.startTranslation(_lastMousePos);
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
            _cam.endTranslation();
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
            //_mesh->subdivide();
            _mesh->saveOBJ();
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
