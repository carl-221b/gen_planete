#include "../include/noisyheight_editor.h"
#include "../include/icosphere.h"

#include <gtest/gtest.h>

TEST(EditorTest, creation_noisyheight) {

    Shape* shape = new Icosphere(DEFAULT_NB_SUBDIVISION);
    Editor* ed = new NoisyHeight_Editor(shape);
    EXPECT_NE (ed,  nullptr);
    delete ed;
    delete shape;
}

TEST(EditorTest, edit_noisyheight) {

    Shape* shape = new Icosphere(DEFAULT_NB_SUBDIVISION);
    Editor* ed = new NoisyHeight_Editor(shape);
    ed->edit();
    EXPECT_NO_FATAL_FAILURE();
    delete ed;
    delete shape;
}

TEST(EditorTest, edit_sameplanet_with_samevalue) {

    Shape* shape = new Icosphere(DEFAULT_NB_SUBDIVISION);
    Shape* shape_bis = new Icosphere(DEFAULT_NB_SUBDIVISION);
    Editor* ed = new NoisyHeight_Editor(shape,10, 10,10,10, 10, nullptr);
    Editor* ed_bis = new NoisyHeight_Editor(shape_bis,10, 10,10,10, 10, nullptr);
    ed->edit();
    ed_bis->edit();
    int length = shape->getVertices()->_positions.size();
    Shape::Vertices* vertices_shape =  shape->getVertices();
    Shape::Vertices* vertices_shape_bis =  shape_bis->getVertices();

    for(int i = 0; i < length; i++){
        //Comparaison problème
        EXPECT_EQ(vertices_shape_bis->_positions[i], vertices_shape->_positions[i]);
        EXPECT_EQ(vertices_shape_bis->_colors[i], vertices_shape->_colors[i]);
        EXPECT_EQ(vertices_shape_bis->_normals[i], vertices_shape->_normals[i]);
    }

    EXPECT_NO_FATAL_FAILURE();
    delete ed;
    delete shape;
}
