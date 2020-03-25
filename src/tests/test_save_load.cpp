#include "../include/noisyheight_editor.h"
#include "../include/icosphere.h"
#include "shape_repository.h"

#include <gtest/gtest.h>

#include <iostream>
#include <fstream>

TEST(Serialisation, save_basic_obj) {

    Shape* shape = new Icosphere(DEFAULT_NB_SUBDIVISION);
    EXPECT_NE (shape,  nullptr);
    //shape->saveOBJ("planet_gtest");
    Shape_Repository::saveOBJ(shape, DATA_DIR"/planet_gtest");

    std::ofstream filewrite ("planet_gtest.obj");
    ASSERT_TRUE(filewrite.is_open());
    filewrite.close();
    ASSERT_FALSE(filewrite.is_open());

    std::ifstream fileread ("planet_gtest.obj");
    ASSERT_TRUE(fileread.is_open());
    fileread.close();
    ASSERT_FALSE(fileread.is_open());

    delete shape;
}

