#include "basic_editor.h"
#include <time.h>

Basic_Editor::~Basic_Editor(){

}


void Basic_Editor::assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors){
    vertices->_colors.push_back(colors);
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
            Eigen::Vector3f vect{0.0f, 0.0f, 0.5f};
            assignColor(vertices, vect);
        }
        else if(factor <= 1.01){
            Eigen::Vector3f vect{0.0f, 0.33f, 0.0f};
            assignColor(vertices,vect);
        }
        else if(factor <= 1.02){
            Eigen::Vector3f vect{0.5f, 0.25f, 0.0f};
            assignColor(vertices, vect);
        }
        else{
            Eigen::Vector3f vect{0.8f, 0.8f, 0.8f};
            assignColor(vertices, vect);
        }

    }
}
