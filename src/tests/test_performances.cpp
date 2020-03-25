#include "../include/noisyheight_editor.h"
#include "../include/icosphere.h"

#include <iostream>
#include <fstream>

#include <gtest/gtest.h>
#include "common.h"

#define NB_TRY 50
#define MAX_SUBDIVISION_NOMODIF 10
#define MAX_SUBDIVISION_MODIF 10

//Test to create performance diagramm
TEST(DISABLED_TimePerformances, nomodif)
{
    std::ofstream out;
    out.open("test_perf_nomodif.txt");

    int sub = 0;
    Timer timer;
    while(sub < MAX_SUBDIVISION_NOMODIF)
    {
        sub ++;
        Shape* shape;

        try{
            out << sub << ";" ;
            for (int i =0; i <NB_TRY ;i++)
            {
                timer.startTimer();
                shape = new Icosphere(sub);
                timer.endTimer();

                double duration = timer.getDurationMs();
                out << duration << ";";
                delete shape;
            }
            out << std::endl;
        }
        catch (const std::bad_alloc&)
        {
            std::cerr << "FAIL TO ALLOC " << sub<< std::endl;
            out.close();
            return;
        }

    }
    std::cout<<"Perfs written to test_perf_nomodif.txt\n";

    out.close();
}

TEST(DISABLED_TimePerformances, withmodif)
{
    std::ofstream out;
    out.open("test_perf_modif.txt");

    int sub = 0;
    Timer timer;
    while(sub < MAX_SUBDIVISION_MODIF)
    {
        sub ++;
        Shape* shape;
        Editor* ed;

        try{
            out << sub << ";" ;
            for (int i =0; i <NB_TRY ;i++)
            {
                timer.startTimer();
                shape = new Icosphere(sub, true);
                ed = new NoisyHeight_Editor(shape);
                ed->edit();
                timer.endTimer();

                double duration = timer.getDurationMs();
                out << duration << ";";
                delete shape;
                delete ed;
            }
            out << std::endl;
        }
        catch (const std::bad_alloc&)
        {
            std::cerr << "FAIL TO ALLOC " << sub<< std::endl;
            std::abort();
        }

    }
    std::cout<<"Perfs written to test_perf_modif.txt\n";

    out.close();
}
