#include "../include/noisyheight_editor.h"
#include "../include/icosphere.h"

#include <gtest/gtest.h>
#include "common.h"

#define AIM_MAX_TIME_MS (0.2 * 10.e3)

TEST(TimeGeneration, limits_subdivision) {

    int sub = 0;
    double duration = 0;
    int nb_vertices = 0;
    while(duration < AIM_MAX_TIME_MS)
    {
        sub ++;

        Timer timer;
        timer.startTimer();

        Shape* shape = new Icosphere(sub);
        Editor* ed = new NoisyHeight_Editor(shape);
        ed->edit();
        EXPECT_NO_FATAL_FAILURE();
        nb_vertices = shape->getVertices()->_positions.size();
        delete ed;
        delete shape;

        timer.endTimer();

        duration = timer.getDurationMs();
    }

    std::cout<<"Maximum subdivision with NoisyHeight_Editor : "<< sub<<" for "<< (duration) <<" ms.\n";
    std::cout<<"Number of vertices : "<< nb_vertices<<" \n";
}

//Graphics TODO
