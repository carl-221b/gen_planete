#ifndef XMLGENERATOR_H
#define XMLGENERATOR_H

#include "generator.h"

class SimpleGenerator : public Generator
{
public:
    SimpleGenerator(std::string& path_config);
    ~SimpleGenerator();

    void loadFileConfig(std::string& filepath);

    Shape* generate();
};

#endif // XMLGENERATOR_H
