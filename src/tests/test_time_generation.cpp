#include "../include/noisyheight_editor.h"
#include "../include/icosphere.h"

#include <gtest/gtest.h>

#include <chrono>
typedef std::chrono::high_resolution_clock Clock;

#define AIM_MAX_TIME_MS (0.2 * 10.e3)

TEST(TimeGeneration, limits_subdivision) {

    int sub = 0;
    double duration = 0;
    while(duration < AIM_MAX_TIME_MS)
    {
        sub ++;

        auto start = Clock::now();

        Shape* shape = new Icosphere(sub);
        Editor* ed = new NoisyHeight_Editor(shape);
        ed->edit();
        EXPECT_NO_FATAL_FAILURE();
        delete ed;
        delete shape;

        auto end = Clock::now();

        duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count();
    }

    std::cout<<"Maximum subdivision with NoisyHeight_Editor : "<< sub<<" for "<< (duration) <<" ms.\n";
}

