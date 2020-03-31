#include "../include/common.h"

#include <gtest/gtest.h>

#include "thresholdtable.h"
#include "noiserandom.h"

TEST(TresholdTest, creation)
{

    int nb_layers = (int)NoiseRandom::random(0,20);
    std::vector<Eigen::Vector4f> colors;
    for(int i=0; i< nb_layers; i++)
    {
        colors.push_back(
                    Eigen::Vector4f(
                        NoiseRandom::random(0,1),
                        NoiseRandom::random(0,1),
                        NoiseRandom::random(0,1),
                        NoiseRandom::random(0,1)));
    }

    ThresholdTable<Eigen::Vector4f> layers(colors.back());

    for (size_t i = 0; i< (colors.size()-1); i++)
    {
        layers.addLayer(i*1.0/colors.size(), colors[i]);
    }

    EXPECT_EQ(layers.getLayers().size(), colors.size());

    size_t i =0;
    for(Threshold<Eigen::Vector4f> lay: layers.getLayers())
    {
        if(i != (layers.getLayers().size()-1))
        {
            EXPECT_EQ(lay._max, i*1.0/colors.size());
        }

        for (int k =0; k <4; k++)
        {
            EXPECT_EQ(lay._data(k), colors[i](k));
        }

        i++;
    }

}


TEST(TresholdTest, getvalue)
{

    int nb_layers = (int)NoiseRandom::random(0,20);
    std::vector<Eigen::Vector4f> colors;
    for(int i=0; i< nb_layers; i++)
    {
        colors.push_back(
                    Eigen::Vector4f(
                        NoiseRandom::random(0,1),
                        NoiseRandom::random(0,1),
                        NoiseRandom::random(0,1),
                        NoiseRandom::random(0,1)));
    }

    ThresholdTable<Eigen::Vector4f> layers(colors.back());

    for (size_t i = 0; i< (nb_layers-1); i++)
    {
        layers.addLayer(i*1.0/nb_layers, colors[i]);
    }

    double ind = NoiseRandom::random(0, nb_layers);
    int layerExpected = std::ceil(ind);
    double value = ind / nb_layers;
    EXPECT_EQ(layers.getDataLayerByValue(value), colors[layerExpected]);

}
