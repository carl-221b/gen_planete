#include "xmlgenerator.h"

#include <pugixml.hpp>

SimpleGenerator::SimpleGenerator(std::string &path_config)
{

}

SimpleGenerator::~SimpleGenerator()
{

}

void SimpleGenerator::loadFileConfig(std::string &filepath)
{
    using namespace pugi;

    xml_document doc;
    xml_parse_result result = doc.load_file("gen_parameters.xml");
    xml_node root = doc.document_element();
    xml_node shapenode = root.child("shape");
    xml_attribute attr;
    std::cout << root.name() << std::endl;
    if (attr = shapenode.attribute("name")) // attribute really exists
    {
         // Read value as string
         std::cout << "read as string: shape=" << attr.value() << std::endl;
    }
}

Shape *SimpleGenerator::generate()
{
    Shape* shape = new Icosphere(DEFAULT_NB_SUBDIVISION);
    Editor* noisy = new NoisyHeight_Editor(shape);
    noisy->edit();
    delete noisy;
    return shape;
}
