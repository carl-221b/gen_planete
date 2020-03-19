#include "random_editor.h"
#include <time.h>
#include <random>

Random_Editor::Random_Editor(Shape *shape, double maximum_displacement_ratio, ColorThresholdTable *layers)
    :Editor(shape), _maximum_displacement_ratio(maximum_displacement_ratio)
{
    if(layers == nullptr)
    {
        Eigen::Vector3f defaultCol{0.2f, 0.2f, 0.2f};
        _layers = new ThresholdTable<Eigen::Vector3f>(defaultCol);

        Eigen::Vector3f sea{0.0f, 0.0f, 0.5f};
        _layers->addLayer(0, sea);

        Eigen::Vector3f ground{0.0f, 0.33f, 0.0f};
        _layers->addLayer(0.5, ground);

        Eigen::Vector3f montain{0.5f, 0.25f, 0.0f};
        _layers->addLayer(0.9, montain);

        Eigen::Vector3f ice{0.8f, 0.8f, 0.8f};
        _layers->addLayer(1.0, ice);
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


void Random_Editor::assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors){
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
        double factor = distribution(generator);
        if(factor > 0.0){
            point *= 1.0 + factor * _maximum_displacement_ratio;
        }
        assignColor(vertices, _layers->getColorLayerByValue(factor));
    }
}
