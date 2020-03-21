#ifndef EDITOR_H
#define EDITOR_H

#include "shape.h"
#include "thresholdtable.h"

#define DEFAULT_MAXIMUM_DISPLACEMENT_RATIO 0.1

/**
 * @brief Interface to be implemented by an editor that will transform a generic icosphere into a given type of planet
 *
 */
class Editor {
public:
    Editor(Shape* shape) {_shape = shape;}
    virtual ~Editor() {}

    /**
     * @brief Applies vertex deplacement and colors the shape
     */
    virtual void edit() = 0;

    /**
     * @brief info
     * @return the informations of editors, overload it to display parameters informations.
     */
    virtual std::string info() const
    {
        return _name;
    }

protected:
    std::string _name;
    Shape* _shape;
};



#endif // EDITOR_H

