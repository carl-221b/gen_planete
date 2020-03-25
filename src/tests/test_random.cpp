#include "../include/common.h"

#include <gtest/gtest.h>

#include "noiserandom.h"

using namespace NoiseRandom;

#define NB_TRY 100

TEST(RandomTest, uniform) {
    for (int i =0; i < NB_TRY; i++ )
    {
        double val = NoiseRandom::random( 0., 1.);
        EXPECT_GE( val , 0.);
        EXPECT_LE( val , 1.);
    }

    for (int i =0; i < NB_TRY; i++ )
    {
        double min = NoiseRandom::random( 0., 100.);
        double max = NoiseRandom::random( min, 100.);
        double val = NoiseRandom::random( min, max);
        EXPECT_GE( val , min);
        EXPECT_LE( val , max);
    }
}

TEST(RandomTest, normalRandom)
{
    double mean = NoiseRandom::random( -100., 100.);
    double val  =0;
    for (int i =0; i < NB_TRY; i++ )
    {
        val += NoiseRandom::normalRandom( mean, 1);
    }
    val /= NB_TRY;
    EXPECT_NEAR( val, mean, 1.);
}

TEST(RandomTest, height) {
    NoiseRandom::HeightNoise noise(10, 10, 10, 10);
    for (int i =0; i < NB_TRY; i++ )
    {
        double x = NoiseRandom::random( -100., 100.);
        double y = NoiseRandom::random( -100., 100.);
        double z = NoiseRandom::random( -100., 100.);
        double val = noise.getValue(Eigen::Vector3f(x, y, z));
        EXPECT_GT( val , -1.);
        EXPECT_LT( val , 1.);
    }
}
