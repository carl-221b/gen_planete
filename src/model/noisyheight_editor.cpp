#include "noisyheight_editor.h"

#include <time.h>
#include <string>

NoisyHeight_Editor::NoisyHeight_Editor(Shape* shape):Editor(shape)
{
    NoisyHeight_Editor(shape, 4+std::rand()%3, 0.5+ (std::rand()%1500)/1000.0, 0.5 + std::rand()%250/1000.0);
}

NoisyHeight_Editor::NoisyHeight_Editor(Shape* shape, int octave, double frequence, double persistence/*, int seed*/): Editor(shape){
    _name = "noisy_height";
    _octave = octave;
    _frequence = frequence;
    _persistence = persistence;
    //_seed = seed;
}

NoisyHeight_Editor::~NoisyHeight_Editor()
{

}

void NoisyHeight_Editor::assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors){
    vertices->_colors.push_back(colors);
}

float altered_channel(float c){
    //-1.5% à 1.5% d'altération
    return c -0.015f + (std::rand()%300/10000.0);

}

void NoisyHeight_Editor::edit(){
    Shape::Vertices* vertices = _shape->getVertices();

    vertices->_colors.resize(0);

    std::srand(time(NULL));

    HeightNoise noise(_frequence ,_octave ,_persistence);

    for(std::vector<Eigen::Vector3f>::iterator it = vertices->_positions.begin() ; it != vertices->_positions.end(); ++it){

        double height = noise.getValue(*it);

        if(height>0){
            *it *= (1 +height * 0.08); //modif pos
        }

        if(height < 0) {
            Eigen::Vector3f vect{0.0f, 0.0f, altered_channel(0.5f)};
            assignColor(vertices,vect);
        }
        else if(height < 0.5){
            Eigen::Vector3f vect{0.0f, altered_channel(0.33f), 0.0f};
            assignColor(vertices, vect);
        }
        else if(height < 0.91){
            Eigen::Vector3f vect{altered_channel(0.44f), altered_channel(0.3f), altered_channel(0.14f)};
            assignColor(vertices, vect);
        }
        else{
            Eigen::Vector3f vect{altered_channel(0.8f), altered_channel(0.8f), altered_channel(0.8f)};
            assignColor(vertices, vect);
        }

    }
    _shape->computeNormals();
    //_shape->updateVertices(vertices);
}

std::string NoisyHeight_Editor::info() const
{
    std::stringstream ss;
    ss <<  Editor::info() << "\nWith parameters\n"
          << "Octave " << _octave << "\n"
          << "Frequence " << _frequence << "\n"
          << "Persistence " << _persistence << "\n"
          /*<< "Seed " << _seed + "\n"*/;

    return ss.str();
}
