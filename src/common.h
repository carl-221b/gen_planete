#ifndef COMMON_H
#define COMMON_H

#include <iostream>
#include <sys/time.h>  

#include <Eigen/Core>

static double Timer_getTime(void)
{
    struct timeval tv;
    struct timezone tz;
    gettimeofday(&tv, &tz);
    return (double)tv.tv_sec + 1.e-6 * (double)tv.tv_usec;
}

typedef double Timer;

static void startTimer(Timer& timer) { timer = Timer_getTime(); }
static void stopTimer(Timer& timer) { timer = Timer_getTime() - timer; }

#endif
