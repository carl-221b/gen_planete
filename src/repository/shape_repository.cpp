#include "shape_repository.h"

#include <iostream>
#include <fstream>

char *Shape_Repository::FILE_SAVE_OUTPUT = DEFAULT_SAVE_PATH;

void Shape_Repository::saveOBJ(Shape* shape, const std::string& filename){
    std::ofstream myfile;
    myfile.open(filename + ".obj");
    myfile << "o planet\n";

    const Shape::Vertices* vertices = shape->getVertices();

    for(unsigned int i=0; i < vertices->_positions.size(); i++){
        Eigen::Vector3f p = vertices->_positions.at(i);
        myfile << "v " << p.x() << " " << p.y() << " " << p.z() << "\n";
        Eigen::Vector3f n = vertices->_normals.at(i);
        myfile << "vn " << n.x() << " " << n.y() << " " << n.z() << "\n";

    }

    const std::vector<Eigen::Vector3i> faces = shape->getFaces();
    for(unsigned int i=0; i < faces.size(); i++){
        Eigen::Vector3i f = faces.at(i);
        myfile << "f " << ( std::to_string(f.x()+1)+"//"+std::to_string(f.x()+1) ) << " " << ( std::to_string(f.y()+1)+"//"+std::to_string(f.y()+1) ) << " " << ( std::to_string(f.z()+1)+ "//" +std::to_string(f.z()+1) ) << "\n";
    }

    myfile.close();
}

void Shape_Repository::saveOFF(Shape* shape, const std::string& filename){
    std::ofstream myfile;
    myfile.open (filename + ".off");
    myfile << "COFF\n";
    const Shape::Vertices* vertices = shape->getVertices();

    myfile << vertices->_positions.size() << " " << shape->getFaces().size() << " 0\n"; // 0 is the (ignored) number of edges

    for(unsigned int i=0; i < vertices->_positions.size(); i++){
        Eigen::Vector3f p = vertices->_positions.at(i);
        Eigen::Vector3f c = vertices->_colors.at(i);
        myfile << p.x() << " " << p.y() << " " << p.z() << " " << (int) (c.x()*255) << " " << (int) (c.y()*255) << " " << (int) (c.z()*255) << " 1\n";

    }

    const std::vector<Eigen::Vector3i> faces = shape->getFaces();
    for(unsigned int i=0; i<faces.size(); i++){
        Eigen::Vector3i f = faces.at(i);
        myfile << "3 " << f.x() << " " << f.y() << " " << f.z() << "\n";
    }

    myfile.close();
}
