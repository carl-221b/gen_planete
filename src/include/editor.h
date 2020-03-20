#ifndef EDITOR_H
#define EDITOR_H

#include "shape.h"
#include "thresholdtable.h"

#define DEFAULT_MAXIMUM_DISPLACEMENT_RATIO 0.1


enum Mode_Aleatory_Flags
{
    NO_ALEATORY         = 0,
    ALEA_OCTAVE         = 1 << 0,
    ALEA_FREQUENCE      = 1 << 1,
    ALEA_PERSISTENCE    = 1 << 2,
    ALEA_SEED           = 1 << 3,
};

inline Mode_Aleatory_Flags operator|(Mode_Aleatory_Flags a, Mode_Aleatory_Flags b)
{
    return static_cast<Mode_Aleatory_Flags>(static_cast<int>(a) | static_cast<int>(b));
}

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

    virtual std::string info() const
    {
        return _name;
    }

    std::string name() const
    {
        return _name;
    }

protected:
    std::string _name;
    Shape* _shape;
};



#endif // EDITOR_H

