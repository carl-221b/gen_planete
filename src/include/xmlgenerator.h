#ifndef XMLGENERATOR_H
#define XMLGENERATOR_H

#include "generator.h"

#include <pugixml.hpp>

// Editors
#include "noisyheight_editor.h"
#include "random_editor.h".h"

//Basic shapes
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

    ColorThresholdTable* readColorThresholdTable(pugi::xml_node& node);

    bool readBool(pugi::xml_node& node);
    int readInt(pugi::xml_node& node);
    double readDouble(pugi::xml_node& node);

    Eigen::Vector3f readVector3f(pugi::xml_node& node);
};

#endif // XMLGENERATOR_H
