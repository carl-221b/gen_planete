#include "opengl.h"
#include "viewer.h"

#include "noisyheight_editor.h"
#include "rendering_opengl.h"

Viewer* v;

const int WIDTH = 1000;
const int HEIGHT = 1200;

static void char_callback(GLFWwindow* window, unsigned int key)
{
    v->charPressed(key);
}

static void scroll_callback(GLFWwindow* window, double x, double y)
{
    v->mouseScroll(x,y);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if ((key == GLFW_KEY_Q || key == GLFW_KEY_ESCAPE) && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, true);
    }

    v->keyPressed(key,action,mods);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
    v->mousePressed(window, button, action);
}

void cursorPos_callback(GLFWwindow* window, double x, double y)
{
    v->mouseMoved(x,y);
}

void  reshape_callback(GLFWwindow* window, int width, int height)
{
    v->reshape(width,height);
}

// initialize GLFW framework
GLFWwindow* initGLFW()
{
    if (!glfwInit())
        exit(EXIT_FAILURE);

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, (GLint)GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, "PDP JUPITER", NULL, NULL);
    if (!window) {
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    glfwMakeContextCurrent(window);
    glbinding::Binding::initialize();
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;
    std::cout << "GLSL version: " << glGetString(GL_SHADING_LANGUAGE_VERSION) << std::endl;

    // callbacks
    glfwSetKeyCallback(window, key_callback);
    glfwSetCharCallback(window, char_callback);
    glfwSetFramebufferSizeCallback(window, reshape_callback);
    glfwSetCursorPosCallback(window, cursorPos_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetScrollCallback(window, scroll_callback);

    return window;
}

static void error_callback(int error, const char* description)
{
    fputs(description, stderr);
}


int main (int argc, char **argv)
{
    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = initGLFW();
    Rendering* rendering = new Rendering_OpenGL();
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    v = new Viewer(rendering);

    Shape* shape = new Icosphere(DEFAULT_NB_SUBDIVISION);


    Editor* noisy = new NoisyHeight_Editor(shape);
    noisy->edit();
    delete noisy;

    /*
    Editor* basic_editor = new Basic_Editor(shape);
    basic_editor->edit();
    delete basic_editor;*/

    shape->init();

    v->init(w, h, shape);

    while (!glfwWindowShouldClose(window))
    {
        // render the scene
        v->updateScene();

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    delete v;
    delete shape;

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
