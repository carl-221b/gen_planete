#ifndef XMLGENERATOR_H
#define XMLGENERATOR_H

#include "generator.h"

#include <pugixml.hpp>

#include "noisyheight_editor.h"
#include "icosphere.h"

/**
 * @brief The XMLGenerator class, the xml implementation of generator.
 */
class XMLGenerator : public Generator
{
public:
    XMLGenerator();
    ~XMLGenerator();

    /**
     * @see generator.h
     */
    Shape* generate(std::string fileconfig);

private:

    /**
     * @brief basicShapeContruct check the corresponding node and construct the basic shape.
     * @param root the root node of the xml document.
     * @return the basic shape.
     */
    Shape* basicShapeContruct(pugi::xml_node& root);

    /**
     * @brief applyEditor apply the editor in configuration file.
     * @param root the root node of the xml document.
     * @param shape the shape to modify.
     */
    void applyEditor(pugi::xml_node& root, Shape* shape);
};

#endif // XMLGENERATOR_H
