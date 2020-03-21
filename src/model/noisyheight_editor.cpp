#include "noisyheight_editor.h"
#include <time.h>
#include <string>
#include "common.h"

NoisyHeight_Editor::NoisyHeight_Editor(Shape* shape)
    :NoisyHeight_Editor(shape, DEFAULT_MAXIMUM_DISPLACEMENT_RATIO,
                        ALEA_OCTAVE      |
                        ALEA_FREQUENCE   |
                        ALEA_PERSISTENCE |
                        ALEA_SEED        ,
                        0,
                        0,
                        0,
                        0)
{
}

NoisyHeight_Editor::NoisyHeight_Editor(Shape* shape,
                                       double maximum_displacement_ratio,
                                       Mode_Aleatory_Flags flags,
                                       int octave,
                                       double frequence,
                                       double persistence,
                                       int seed,
                                       ColorThresholdTable *layers):
    Editor(shape), _maximum_displacement_ratio(maximum_displacement_ratio), _octave(octave), _frequence(frequence), _persistence(persistence), _seed(seed)
{
    _name = "noisy_height";

    if(ALEA_OCTAVE & flags)
        _octave = (int)NoiseRandom::random(1, 20);
    if(ALEA_FREQUENCE & flags)
        _frequence = NoiseRandom::random(0.2, 8.0);
    if(ALEA_PERSISTENCE & flags)
        _persistence = NoiseRandom::random(0.0, 1.0);
    if(ALEA_SEED & flags)
        _seed = (int)NoiseRandom::random(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());

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

NoisyHeight_Editor::~NoisyHeight_Editor()
{
    delete _layers;
}

void NoisyHeight_Editor::assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors){
    vertices->_colors.push_back(colors);
}

void NoisyHeight_Editor::edit()
{
    Shape::Vertices* vertices = _shape->getVertices();
    vertices->_colors.resize(0);


    NoiseRandom::HeightNoise noise(_seed, _frequence, _octave, _persistence);

    for(Eigen::Vector3f& point : vertices->_positions)
    {
        double heightFactor = noise.getValue(point);

        point *= (1 + heightFactor * _maximum_displacement_ratio);
        
        Eigen::Vector3f color = _layers->getColorLayerByValue(heightFactor);
        color = color + color * NoiseRandom::random(-0.15, 0.15);
        assignColor(vertices, color);
    }
    _shape->computeNormals();
}

std::string NoisyHeight_Editor::info() const
{
    std::stringstream ss;
    ss <<  Editor::info() << "\nWith parameters\n"
        << "Octave " << _octave << "\n"
        << "Frequence " << _frequence << "\n"
        << "Persistence " << _persistence << "\n"
        << "Seed " << _seed << "\n";

    for (Threshold<Eigen::Vector3f> tr : _layers->getLayers())
    {
        ss << "max : " << tr._max <<" \ncolor :\n"<< tr._data << "\n\n";
    }

    return ss.str();
}
