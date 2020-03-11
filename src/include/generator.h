#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>

#include "noisyheight_editor.h"

#include "icosphere.h"

#include "shape.h"

enum enum_basic_shape{
    ICOSPHERE,
};

enum enum_editor{
    BASIC_HEIGHT,
    NOISY_HEIGHT
};

class Generator
{
public:
    Generator();
    virtual ~Generator();

    virtual void loadFileConfig(std::string& filepath) = 0;

    virtual Shape* generate() = 0;

private:

    Shape* InstantiateBasicShape(std::string& name_shape);

    Shape* applyEditor(std::string& name_ed);

};

#endif // GENERATOR_H
