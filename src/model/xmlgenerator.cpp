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
    std::cout << "Load result: " << result.description() << std::endl;
    if(result.status != status_ok)
    {
        throw new std::runtime_error("Problem opening config file.");
    }
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
    if ((name_attr = shapenode.attribute("name"))) // attribute really exists
    {
        name = name_attr.as_string();
    }
    else throw std::runtime_error("No attribute \"name\ in node basic_shape");

    //Switch parameters
    if(name == "icosphere")
    {
        //Default parameters
        int nb_subdivision = DEFAULT_NB_SUBDIVISION;
        bool organic = false;

        xml_node shape_params;
        if((shape_params = root.child("shape_params")))
        {
            xml_node opt;

            if ((opt = shape_params.child("nb_subdivision"))) // attribute really exists
            {
                nb_subdivision = readInt(opt);
            }
            if ((opt = shape_params.child("organic"))) // attribute really exists
            {
                organic = readBool(opt);
            }
        }

        std::cout << "Basic shape : " << name <<" subdivided "<< nb_subdivision <<" times \n";
        std::cout << "With : organic " << (organic?"true":"false") <<"\n";
        return new Icosphere(nb_subdivision, organic);

    }
    else throw std::runtime_error("Not implemented basic_shape.");
}

void XMLGenerator::applyEditor(pugi::xml_node &root, Shape *shape)
{
    using namespace pugi;

    Editor* ed;

    xml_node editorenode = root.child("editor");

    //Choose basic_shape
    xml_attribute name_attr;
    std::string name;
    if ((name_attr = editorenode.attribute("name"))) // attribute really exists
    {
        name = name_attr.as_string();
    }
    else throw std::runtime_error("No attribute \"name\" in node editor");

    //Switch parameters
    if(name == "noisy_height")
    {
        //Default parameters
        double maximum_displacement_ratio = DEFAULT_MAXIMUM_DISPLACEMENT_RATIO;
        ColorThresholdTable* colors_threshold = nullptr;

        ed = new NoisyHeight_Editor(shape);
    }
    else if(name == "random")
    {
        //Default parameters
        double maximum_displacement_ratio = DEFAULT_MAXIMUM_DISPLACEMENT_RATIO;
        ColorThresholdTable* colors_threshold = nullptr;

        xml_node editor_params;
        if((editor_params = root.child("editor_params")))
        {
            xml_node child;
            if ((child = editor_params.child("maximum_displacement_ratio")))
            {
                maximum_displacement_ratio = readDouble(child);
            }

            if ((child = editor_params.child("colors_treshold")))
            {
                colors_threshold = readColorThresholdTable(child);
            }
        }

        ed = new Random_Editor(shape, maximum_displacement_ratio, colors_threshold);
    }
    else throw std::runtime_error("Not implemented editor.");

    std::cout << "Editor : " << ed->info() <<" \n";
    ed->edit();
    delete ed;
}

ColorThresholdTable *XMLGenerator::readColorThresholdTable(pugi::xml_node &node)
{
    using namespace pugi;

    ColorThresholdTable* colors_threshold = nullptr;

    Eigen::Vector3f color;
    xml_node chilNode;
    if ((chilNode = node.child("default_color")))
    {
        color = readVector3f(chilNode);
        colors_threshold = new ColorThresholdTable(color);
    }
    else colors_threshold = new ColorThresholdTable();

    if ((chilNode = node.child("table")))
    {
        for(xml_node treshold : chilNode.children("layer"))
        {
            xml_node child= treshold.child("max_treshold");
            double value = readDouble(child);

            child = treshold.child("color");
            color = readVector3f(child);
            colors_threshold->addLayer(value, color);
        }
    }
    return colors_threshold;
}

bool XMLGenerator::readBool(pugi::xml_node &node)
{
    using namespace pugi;
    xml_attribute attr = node.first_attribute();
    return attr.as_bool();
}

int XMLGenerator::readInt(pugi::xml_node &node)
{
    using namespace pugi;
    xml_attribute attr = node.first_attribute();
    return attr.as_int();
}

double XMLGenerator::readDouble(pugi::xml_node &node)
{
    using namespace pugi;
    xml_attribute attr = node.first_attribute();
    return attr.as_double();

}

Eigen::Vector3f XMLGenerator::readVector3f(pugi::xml_node &node)
{
    using namespace pugi;
    Eigen::Vector3f vect;
    int i = 0;
    for(xml_attribute val_attr: node.child("vector3f").attributes())
    {
        vect(i) = val_attr.as_double();
        i++;
    }
    return vect;
}
