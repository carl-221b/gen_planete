#include "basic_editor.h"
#include <time.h>

Basic_Editor::~Basic_Editor(){

}


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
