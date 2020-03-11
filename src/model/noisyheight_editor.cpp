#include "noisyheight_editor.h"
#include <time.h>


NoisyHeight_Editor::~NoisyHeight_Editor()
{

}

void NoisyHeight_Editor::assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors){
    vertices->_colors.push_back(colors);
}

float altered_channel(float c){
    float res = c -0.015f + (std::rand()%300/10000.0);
    printf("%f\n",res);
    return std::max(0.0f, std::min(1.0f, res));
}

void NoisyHeight_Editor::edit(){
    Shape::Vertices* vertices = _shape->getVertices();

    vertices->_colors.resize(0);

    std::srand(time(NULL));

    HeightNoise noise;

    for(std::vector<Eigen::Vector3f>::iterator it = vertices->_positions.begin() ; it != vertices->_positions.end(); ++it){

        double height = noise.getValue(*it);

        if(height>0){
            *it *= (1 +height * 0.1); //modif pos
        }

        if(height < 0) {
            Eigen::Vector3f vect{altered_channel(0.0f), altered_channel(0.0f), altered_channel(0.5f)};
            assignColor(vertices,vect);
        }
        else if(height < 0.45){
            Eigen::Vector3f vect{altered_channel(0.0f), altered_channel(0.33f), altered_channel(0.0f)};
            assignColor(vertices, vect);
        }
        else if(height < 0.84){
            Eigen::Vector3f vect{altered_channel(0.44f), altered_channel(0.3f), altered_channel(0.14f)};
            assignColor(vertices, vect);
        }
        else{
            Eigen::Vector3f vect{altered_channel(0.8f), altered_channel(0.8f), altered_channel(0.8f)};
            assignColor(vertices, vect);
        }

    }

    //_shape->updateVertices(vertices);
}
