#include "basic_editor.h"
#include <time.h>

Basic_Editor::~Basic_Editor(){

}
/*
void Basic_Editor::modifyShape(){


    Surface_mesh::Face_property<Color> fcolors = surface_mesh.get_face_property<Color>("v:color");

    Surface_mesh::Face_iterator fit;

    Color* col = new Color(0,0,0);
    for(fit = surface_mesh.faces_begin(); fit != surface_mesh.faces_end(); ++fit){
        fcolors[*fit];
    }


    Surface_mesh::Vertex_property<Point> vertices = surface_mesh.get_vertex_property<Point>("v:point");
    Surface_mesh::Vertex_iterator vit;

    for(vit = surface_mesh.vertices_begin(); vit != surface_mesh.vertices_end(); ++vit)
    {
        vertices[*vit] = Point(0,0,50);
    }

}*/
void Basic_Editor::assignColor(Shape::Vertices* vertices, float r, float g, float b){
    vertices->_colors.push_back(r);
    vertices->_colors.push_back(g);
    vertices->_colors.push_back(b);
}

void Basic_Editor::edit(){
    Shape::Vertices* vertices = _shape->getVertices();

    vertices->_colors.resize(0);

    std::srand(time(NULL));

    int i = 0;
    for(std::vector<Eigen::Vector3f>::iterator it = vertices->_positions.begin() ; it != vertices->_positions.end(); ++it){
        float factor = (980.0+ std::rand()%50) / 1000.0;

        if(i == 0){
            std::cout << *it << std::endl;
        }

        if(factor > 1.0){
            *it *= factor; //modif pos
        }

        if(i == 0){
            std::cout << *it << std::endl;
            i++;
        }

        if(factor <1.0) {
            assignColor(vertices, 0.0f, 0.0f, 0.5f);
        }
        else if(factor <= 1.01){
            assignColor(vertices, 0.0f, 0.33f, 0.0f);
        }
        else if(factor <= 1.02){
            assignColor(vertices, 0.5f, 0.25f, 0.0f);
        }
        else{
            assignColor(vertices, 0.8f, 0.8f, 0.8f);
        }
    }

    _shape->updateVertices(vertices);
}
