#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>
#include <sys/time.h>

static struct tms start_cpu_time;
static struct tms end_cpu_time;
static struct timeval start_real_time;
static struct timeval end_real_time;

static inline void start_timer() {
    gettimeofday(&start_real_time, NULL);
    times(&start_cpu_time);
}

static inline void stop_timer() {
    gettimeofday(&end_real_time, NULL);
    times(&end_cpu_time);
}

static inline void print_statistics(int iterations) {
    long ticks_per_second = sysconf(_SC_CLK_TCK);
    double user_time = (double)(end_cpu_time.tms_utime - start_cpu_time.tms_utime) / ticks_per_second;
    double system_time = (double)(end_cpu_time.tms_stime - start_cpu_time.tms_stime) / ticks_per_second;

    double elapsed_real_time = (end_real_time.tv_sec - start_real_time.tv_sec) + 
                               (end_real_time.tv_usec - start_real_time.tv_usec) / 1000000.0;

    printf("User time: %.2f seconds\n", user_time);
    printf("System time: %.2f seconds\n", system_time);
    printf("Real time: %.2f seconds\n", elapsed_real_time);

    double iterations_per_second = iterations / elapsed_real_time;

    printf("Iterations per second: %.2f\n", iterations_per_second);
}

#endif // TIMER_H
