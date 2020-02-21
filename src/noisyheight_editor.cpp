#include "noisyheight_editor.h"
#include <time.h>


NoisyHeight_Editor::~NoisyHeight_Editor()
{

}

void NoisyHeight_Editor::assignColor(Shape::Vertices* vertices, float r, float g, float b){
    vertices->_colors.push_back(r);
    vertices->_colors.push_back(g);
    vertices->_colors.push_back(b);
}

void NoisyHeight_Editor::edit(){
    Shape::Vertices* vertices = _shape->getVertices();

    vertices->_colors.resize(0);

    std::srand(time(NULL));

    int i = 0;
    for(std::vector<Eigen::Vector3f>::iterator it = vertices->_positions.begin() ; it != vertices->_positions.end(); ++it){

        if(i == 0){
            std::cout << *it << std::endl;
        }

        HeightNoise noise;
        double height = noise.getValue(*it);

        if(height>0){
            *it *= (.5 +height * 0.05); //modif pos
        }
        else
        {
            *it *= (.5); //modif pos
        }

        if(i == 0){
            //std::cout << *it << std::endl;
            i++;
        }
        std::cout << "Height : " << height << std::endl;

        if(height < 0) {
            assignColor(vertices, 0.0f, 0.0f, 0.5f);
        }
        else if(height < 1){
            assignColor(vertices, 0.0f, 0.33f, 0.0f);
        }
        else if(height >= 1){
            assignColor(vertices, 0.5f, 0.25f, 0.0f);
        }
        else{
            assignColor(vertices, 0.8f, 0.8f, 0.8f);
        }

    }

    //_shape->updateVertices(vertices);
}
