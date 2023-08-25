#ifndef TIMER_H
#define TIMER_H

#include <stdio.h>
#include <unistd.h>
#include <sys/times.h>

static struct tms start_cpu_time;
static struct tms end_cpu_time;
static clock_t start_real_time;
static clock_t end_real_time;

static inline void start_timer() {
    start_real_time = times(&start_cpu_time);
}

static inline void stop_timer() {
    end_real_time = times(&end_cpu_time);
}

static inline void print_statistics(int iterations) {
    long ticks_per_second = sysconf(_SC_CLK_TCK);
    double user_time = (double)(end_cpu_time.tms_utime - start_cpu_time.tms_utime) / ticks_per_second;
    double system_time = (double)(end_cpu_time.tms_stime - start_cpu_time.tms_stime) / ticks_per_second;
    double real_time = (double)(end_real_time - start_real_time) / ticks_per_second;
    double total_cpu_time = user_time + system_time;
    double iterations_per_second = iterations / total_cpu_time;

    printf("User time: %.2f seconds\n", user_time);
    printf("System time: %.2f seconds\n", system_time);
    printf("Total CPU time: %.2f seconds\n", total_cpu_time);
    printf("Real time: %.2f seconds\n", real_time);
    printf("Iterations per second (based on CPU time): %.2f\n", iterations_per_second);
}

#endif // TIMER_H
