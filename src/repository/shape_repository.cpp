#include "shape_repository.h"

#include <iostream>
#include <fstream>

void Shape_Repository::saveOBJ(Shape* shape, const std::string& filename){
    std::ofstream myfile;
    myfile.open(filename + ".obj");
    myfile << "o planet\n";

    for(unsigned int i=0; i < shape->getVertices()->_positions.size(); i++){
        Eigen::Vector3f p = shape->getVertices()->_positions.at(i);
        myfile << "v " << p.x() << " " << p.y() << " " << p.z() << "\n";
        Eigen::Vector3f n = shape->getVertices()->_normals.at(i);
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
    myfile << "OFF\n";
    myfile << shape->getVertices()->_positions.size() << " " << shape->getFaces().size() << " 0\n"; // 0 is the (ignored) number of edges

    for(unsigned int i=0; i<shape->getVertices()->_positions.size(); i++){
        Eigen::Vector3f p = shape->getVertices()->_positions.at(i);
        myfile << p.x() << " " << p.y() << " " << p.z() << "\n";
    }

    const std::vector<Eigen::Vector3i> faces = shape->getFaces();
    for(unsigned int i=0; i<faces.size(); i++){
        Eigen::Vector3i f = faces.at(i);
        myfile << "3 " << f.x() << " " << f.y() << " " << f.z() << "\n";
    }

    myfile.close();
}
