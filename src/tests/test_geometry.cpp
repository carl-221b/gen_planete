#include "../include/mesh.h"

#include <gtest/gtest.h>

TEST(GeneralTest, creation) {

    Shape* shape = new Mesh(DATA_DIR"/models/icosa.obj");
    EXPECT_NE (shape,  nullptr);
}

TEST(GeometryTest, creation) {

    Shape* shape = new Mesh(DATA_DIR"/models/icosa.obj");
    EXPECT_NE (shape,  nullptr);
}
