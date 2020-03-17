#ifndef GENERATOR_H
#define GENERATOR_H

#include <iostream>
#include <string.h>

#include "shape.h"

#define DEFAULT_CONFIG_FILE "../src/data/generators/simple.xml"
/**
 * @brief The Generator class, permit to read a given configuration file and generate a planet.
 */
class Generator
{
public:
    Generator(){}
    virtual ~Generator(){}

    /**
     * @brief generate a planet while reading a configuration file.
     * @param fileconfig the path to the configuration file.
     * @return Shape* the planet allocated, must be free whent not needed anymore.
     */
    virtual Shape* generate(std::string fileconfig) = 0;
};

#endif // GENERATOR_H
