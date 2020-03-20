#ifndef RANDOM_EDITOR_H
#define RANDOM_EDITOR_H

#include "editor.h"

#define RANDOM_ED_DEFAULT_MAXIMUM_DISPLACEMENT_RATIO 0.1

/**
 * @brief Applies a random modification to the position (x,y,z) of each vertex and applies color depending on the new position.
 * This class allows to transform a generic icosphere into a simple planet
 */
class Random_Editor : public Editor {
public:

    Random_Editor(Shape* shape,
                  double maximum_displacement_ratio = RANDOM_ED_DEFAULT_MAXIMUM_DISPLACEMENT_RATIO,
                  ColorThresholdTable *layers = nullptr);
    ~Random_Editor();

    /**
     * @brief Applies vertex deplacement and colors the shape
     */
    virtual void edit();

    virtual std::string info() const;

protected:

private:
    /**
     * @brief Assigns color for a vertex
     *
     * @param vertices Structure that contains the vertex data
     * @param colors : vector of 3 floats,
     * each float is a color of the vertex (red, green and blue).
     * Each float value is in [0,1].
     */
    void assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors);

private:

    double _maximum_displacement_ratio;
    ColorThresholdTable* _layers;

};

#endif // RANDOM_EDITOR_H


