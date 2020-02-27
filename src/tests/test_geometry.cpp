#include "../include/mesh.h"
#include "../include/shape.h"

#include <gtest/gtest.h>

TEST(GeometryTest, creation) {

    Shape* shape = new Mesh(DATA_DIR"/models/icosa.obj");
    EXPECT_NE (shape,  nullptr);
    delete shape;
}

TEST(GeometryTest, vertices) {

    Shape* shape = new Mesh(DATA_DIR"/models/icosa.obj");
    Shape::Vertices* v = shape->getVertices();
    int size = v->_positions.size();

    EXPECT_NE(size, 0);
    EXPECT_EQ(v->_colors.size(), size);
    EXPECT_EQ(v->_normals.size(), size);
    delete shape;
}
