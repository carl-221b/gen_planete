#include "../include/common.h"

#include <gtest/gtest.h>

#define PRECISION_NEED (10e-4)

TEST(CoordinatesTest, cartToPolar) {

    Eigen::Vector3f cart(0, std::sqrt(2.), std::sqrt(2.));
    Eigen::Vector3f polar_expected(2., M_PI/4., M_PI/2.);
    Eigen::Vector3f res = cartesianToSphericalCoord(cart);

    ASSERT_NEAR(polar_expected.x(), res.x(), PRECISION_NEED);
    ASSERT_NEAR(polar_expected.y(), res.y(), PRECISION_NEED);
    ASSERT_NEAR(polar_expected.z(), res.z(), PRECISION_NEED);
}

TEST(CoordinatesTest, polarToCart) {

    Eigen::Vector3f polar(2., M_PI/4., M_PI/2.);
    Eigen::Vector3f cart_expected(0., std::sqrt(2.), std::sqrt(2.));
    Eigen::Vector3f res = sphericalToCartesianCoord(polar);

    ASSERT_NEAR(cart_expected.x(), res.x(), PRECISION_NEED);
    ASSERT_NEAR(cart_expected.y(), res.y(), PRECISION_NEED);
    ASSERT_NEAR(cart_expected.z(), res.z(), PRECISION_NEED);
}

TEST(CoordinatesTest, cart0) {

    Eigen::Vector3f cart(0, 0, 0);
    ASSERT_THROW(cartesianToSphericalCoord(cart), std::runtime_error);
}

TEST(CoordinatesTest, polar0) {

    Eigen::Vector3f polar(0, 1, 1);
    ASSERT_THROW(sphericalToCartesianCoord(polar), std::runtime_error);
}

TEST(CoordinatesTest, cumulated) {

    for (double x = -1; x<=1; x+=0.2)
    {
        for (double y = -1; y<=1; y+=0.2)
        {
            for (double z = -1; z<=1; z+=0.2)
            {
                if(x ==0.0 && y ==0.0 && z==0.0)
                {
                    continue;
                }
                //std::cout << x <<" "<< y <<" "<< z<< " done" <<std::endl;

                Eigen::Vector3f cart(x, y, z);
                Eigen::Vector3f tmp = cartesianToSphericalCoord(cart);
                Eigen::Vector3f res = sphericalToCartesianCoord(tmp);

                ASSERT_NEAR(cart.x(), res.x(), PRECISION_NEED);
                ASSERT_NEAR(cart.y(), res.y(), PRECISION_NEED);
                ASSERT_NEAR(cart.z(), res.z(), PRECISION_NEED);
            }
        }
    }
}
