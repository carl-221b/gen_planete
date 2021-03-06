#include <getopt.h>

#include "opengl.h"
#include "viewer.h"

#include "shape.h"
#include "icosphere.h"
#include "noisyheight_editor.h"
#include "rendering_opengl.h"
#include "xmlgenerator.h"
#include "shape_repository.h"

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
    if ((key == GLFW_KEY_A || key == GLFW_KEY_ESCAPE) && action == GLFW_PRESS) {
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

static void usage(){

    printf("Use: ./gen_planet [options] [config_file_path]\n");
    printf("The program generate and construct a whole planet with differents options.\n");
    printf("You can use it without config_file_path, but it's recommended in order to control the parameters.\n");
    printf("\n");
    printf("Options: \n");
    printf("-h         Displays this help\n");
    printf("-o         The filename output when saving.\n");
}

int main (int argc, char **argv)
{
    //Options and main parameters 
    int opt = 0;
    while ((opt = getopt(argc, argv, "ho:")) != -1) {
        switch (opt) {
        case 'h':
            usage();
            exit(EXIT_SUCCESS);
            break;
        case 'o':
            Shape_Repository::FILE_SAVE_OUTPUT = optarg;
            printf("New save path : %s\n", Shape_Repository::FILE_SAVE_OUTPUT);
            break;
        default:
            usage();
            exit(EXIT_FAILURE);
        }
    }

    //Generation
    Shape* shape;

    if (optind >= argc) { //if no config_file_path
        shape = new Icosphere(5, true);
        Editor* noisy = new NoisyHeight_Editor(shape);
        noisy->edit();
        delete noisy;
    }else{
        std::string config_path = std::string(argv[optind]);
        std::cout << "File config generator : " << config_path << std::endl;

        XMLGenerator parameters;
        shape = parameters.generate(config_path);
    }

    // Visualisation

    glfwSetErrorCallback(error_callback);

    GLFWwindow* window = initGLFW();
    Rendering* rendering = new Rendering_OpenGL();
    int w, h;
    glfwGetFramebufferSize(window, &w, &h);

    v = new Viewer(rendering);
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
    delete rendering;

    glfwDestroyWindow(window);
    glfwTerminate();
    exit(EXIT_SUCCESS);
}
