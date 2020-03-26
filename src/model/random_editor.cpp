#include "random_editor.h"
#include <time.h>
#include <random>

Random_Editor::Random_Editor(Shape *shape, double maximum_displacement_ratio, ColorThresholdTable *layers)
    :Editor(shape), _maximum_displacement_ratio(maximum_displacement_ratio)
{
    _name = "random";
    if(layers == nullptr)
    {
        //Default colors layer
        _layers = DefaultColorThresholdTable();
    }
    else
    {
        _layers = layers;
    }
}

Random_Editor::~Random_Editor()
{
    delete _layers;
}


inline void Random_Editor::assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors){
    vertices->_colors.push_back(colors);
}

void Random_Editor::edit(){
    Shape::Vertices* vertices = _shape->getVertices();

    vertices->_colors.resize(0);

    std::srand(time(NULL));
    std::default_random_engine generator;
    std::uniform_real_distribution<double> distribution(-1, 1);

    for(Eigen::Vector3f& point : vertices->_positions)
    {
        double heightFactor = distribution(generator);

        point *= 1.0 + heightFactor * _maximum_displacement_ratio;
        
        Eigen::Vector3f color = _layers->getColorLayerByValue(heightFactor);
        assignColor(vertices, color);
    }
     _shape->computeNormals();
}

std::string Random_Editor::info() const
{
    std::stringstream ss;
    ss <<  Editor::info() << "\nWith parameters\n"
          << "maximum_displacement_ratio " << _maximum_displacement_ratio << "\n"
          << "Layers : \n";

    for (Threshold<Eigen::Vector3f> tr : _layers->getLayers())
    {
        ss << "max : " << tr._max <<" \ncolor :\n"<< tr._data << "\n\n";
    }

    return ss.str();
}
