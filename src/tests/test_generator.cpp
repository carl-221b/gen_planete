#include "../include/xmlgenerator.h"

#include <gtest/gtest.h>

TEST(GeneratorTest, creation) {

    XMLGenerator parameters;
    Shape* shape = parameters.generate(DEFAULT_CONFIG_FILE);
    EXPECT_NE (shape,  nullptr);
    delete shape;
}
