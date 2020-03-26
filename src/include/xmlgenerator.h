#ifndef XMLGENERATOR_H
#define XMLGENERATOR_H

#include "generator.h"

#include <pugixml.hpp>

// Editors
#include "noisyheight_editor.h"
#include "random_editor.h"

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
    Shape* generate(const std::string& fileconfig);

private:

    /**
     * @brief basicShapeContruct check the corresponding node and construct the basic shape.
     * @param root the root node of the xml document.
     * @return the basic shape.
     */
    Shape* basicShapeContruct(const pugi::xml_node& root);

    /**
     * @brief applyEditor apply the editor in configuration file.
     * @param root the root node of the xml document.
     * @param shape the shape to modify.
     */
    void applyEditor(const pugi::xml_node& root, Shape* shape);

    //Readers of specifics nodes
    ColorThresholdTable* readColorThresholdTable(const pugi::xml_node& node) const;
    bool readBool(const pugi::xml_node& node) const;
    int readInt(const pugi::xml_node& node) const;
    double readDouble(const pugi::xml_node& node) const;
    Eigen::Vector3f readVector3f(const pugi::xml_node& node) const;
};

#endif // XMLGENERATOR_H
