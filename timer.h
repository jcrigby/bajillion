#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <sys/time.h>

static struct timeval start_time, end_time;
static double elapsed_time;

static inline void start_timer() {
    gettimeofday(&start_time, NULL);
}

static inline void stop_timer() {
    gettimeofday(&end_time, NULL);
    elapsed_time = (end_time.tv_sec - start_time.tv_sec) + ((end_time.tv_usec - start_time.tv_usec) / 1000000.0);
}

static inline void print_statistics(int iterations) {
    double iterations_per_second = iterations / elapsed_time;
    printf("Elapsed time: %.2f seconds\nIterations per second: %.2f\n", elapsed_time, iterations_per_second);
}

#endif // TIMER_H
