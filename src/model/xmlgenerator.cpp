#include "xmlgenerator.h"
#include <exception>

#include <pugixml.hpp>

XMLGenerator::XMLGenerator()
{
}

XMLGenerator::~XMLGenerator()
{
}

Shape* XMLGenerator::generate(std::string fileconfig)
{
    using namespace pugi;

    xml_document doc;
    xml_parse_result result = doc.load_file(fileconfig.c_str());
    xml_node root = doc.document_element();

    //Basic_shape
    Shape* shape = basicShapeContruct(root);

    //Editor
    applyEditor(root, shape);

    return shape;
}

Shape *XMLGenerator::basicShapeContruct(pugi::xml_node &root)
{
    using namespace pugi;

    xml_node shapenode = root.child("basic_shape");

    //Choose basic_shape
    xml_attribute name_attr;
    std::string name;
    if (name_attr = shapenode.attribute("name")) // attribute really exists
    {
         name = name_attr.as_string();
    }
    else throw std::runtime_error("No attribute \"name\ in node basic_shape");

    //Switch parameters
    if(name == "icosphere")
    {
        xml_attribute nb_subdiv_attr;
        int nb_subdivision = DEFAULT_NB_SUBDIVISION;
        if (nb_subdiv_attr = shapenode.attribute("nb_subdivision")) // attribute really exists
        {
             nb_subdivision = nb_subdiv_attr.as_int();
        }
        std::cout << "Basic shape : " << name <<" subdivided "<< nb_subdivision <<" times \n";
        return new Icosphere(nb_subdivision);

    }
    else throw std::runtime_error("Not implemented basic_shape.");
}

void XMLGenerator::applyEditor(pugi::xml_node &root, Shape *shape)
{
    using namespace pugi;

    xml_node shapenode = root.child("editor");

    //Choose basic_shape
    xml_attribute name_attr;
    std::string name;
    if (name_attr = shapenode.attribute("name")) // attribute really exists
    {
         name = name_attr.as_string();
    }
    else throw std::runtime_error("No attribute \"name\ in node editor");

    //Switch parameters
    if(name == "noisy_height")
    {
        std::cout << "Editor : " << name <<" \n";
        NoisyHeight_Editor noisy(shape);
        noisy.edit();
    }
    else throw std::runtime_error("Not implemented editor.");
}
