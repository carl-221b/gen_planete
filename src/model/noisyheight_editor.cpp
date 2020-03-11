#include "noisyheight_editor.h"
#include <time.h>


NoisyHeight_Editor::~NoisyHeight_Editor()
{

}

void NoisyHeight_Editor::assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors){
    vertices->_colors.push_back(colors);
}


void NoisyHeight_Editor::edit(){
    Shape::Vertices* vertices = _shape->getVertices();

    vertices->_colors.resize(0);

    std::srand(time(NULL));

    int i = 0;
    for(std::vector<Eigen::Vector3f>::iterator it = vertices->_positions.begin() ; it != vertices->_positions.end(); ++it){

        HeightNoise noise;
        double height = noise.getValue(*it);

        if(height>0){
            *it *= (1 +height * 0.05); //modif pos
        }

        if(height < 0) {
            Eigen::Vector3f vect{0.0f, 0.0f, 0.5f};
            assignColor(vertices,vect);
        }
        else if(height < 0.45){
            Eigen::Vector3f vect{0.0f, 0.33f, 0.0f};
            assignColor(vertices, vect);
        }
        else if(height < 0.8){
            Eigen::Vector3f vect{0.5f, 0.25f, 0.0f};
            assignColor(vertices, vect);
        }
        else{
            Eigen::Vector3f vect{0.6f, 0.6f, 0.6f};
            assignColor(vertices, vect);
        }

    }

    //_shape->updateVertices(vertices);
}
