#include "../include/icosphere.h"
#include "../include/shape.h"

#include <gtest/gtest.h>

#define MAX_SUBDIVIDE_TEST 3

TEST(IcosphereTest, creation) {

    Shape* shape = new Icosphere(DEFAULT_NB_SUBDIVISION);
    EXPECT_NE (shape,  nullptr);
    delete shape;
}

TEST(IcosphereyTest, vertices) {

    Shape* shape = new Icosphere(DEFAULT_NB_SUBDIVISION);
    const Shape::Vertices* v = shape->getVertices();
    int size = v->_positions.size();

    EXPECT_NE(size, 0);
    EXPECT_EQ(v->_colors.size(), size);
    EXPECT_EQ(v->_normals.size(), size);
    delete shape;
}

TEST(IcosphereTest, subdivide_0) {

    Shape* shape = new Icosphere(0);
    const Shape::Vertices* v = shape->getVertices();
    int sizeVertices = v->_positions.size();
    EXPECT_EQ(sizeVertices, 12);

    //int sizeFaces = shape->getFaces().size();
    //EXPECT_EQ(sizeFaces, 20);

    //Maybe not necessary
    //int sizeEdges = shape->getEdges().size();
    //EXPECT_EQ(sizeEdges, 30);

    delete shape;
}

TEST(IcosphereTest, subdivide_random) {

    int nbsub = std::rand() % MAX_SUBDIVIDE_TEST ;

    std::cout << "Number subdivision : " << nbsub << std::endl;

    Shape* shape = new Icosphere(nbsub);
    const Shape::Vertices* v = shape->getVertices();
    int sizeVertices = v->_positions.size();

    std::cout << "Number vertices : " << sizeVertices << std::endl;

    //int aimedSizeVertices =
    //EXPECT_EQ(sizeVertices, aimedSizeVertices);

    //Attributes same size
    EXPECT_EQ(v->_colors.size(), sizeVertices);
    EXPECT_EQ(v->_normals.size(), sizeVertices);

    delete shape;
}

