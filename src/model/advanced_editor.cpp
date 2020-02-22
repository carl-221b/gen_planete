#include "advanced_editor.h"




Advanced_Editor::~Advanced_Editor(){

}


void Advanced_Editor::assignColor(Shape::Vertices* vertices, Eigen::Vector3f colors){
    vertices->_colors.push_back(colors);
}


void Advanced_Editor::edit(){

}
