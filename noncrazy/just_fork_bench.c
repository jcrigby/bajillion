#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "timer.h"  // Include your timer header here

int main(int argc, char *argv[]) {
    int verbose = 0;  // Default to not verbose
    int iterations = 1000000;  // Default number of iterations

    // Parse command line options
    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--verbose") == 0) {
            verbose = 1;  // Enable verbose mode if "--verbose" argument is provided
        } else if (strcmp(argv[i], "--iterations") == 0 && i + 1 < argc) {
            iterations = atoi(argv[i + 1]);  // Set custom number of iterations
        }
    }

    // Start the timer
    start_timer();

    pid_t child_pid;
    int status;

    for (int i = 0; i < iterations; ++i) {
        child_pid = fork();

        if (child_pid == 0) {
            // This is the child process. Just exit immediately.
            exit(0);
        } else if (child_pid > 0) {
            // This is the parent process.
            if (verbose) {
                printf("Spawned child process %d\n", i + 1);
            }

            // Wait for the child process to exit.
            waitpid(child_pid, &status, 0);

            if (verbose) {
                if (WIFEXITED(status)) {
                    printf("Child process %d exited with status %d\n", i + 1, WEXITSTATUS(status));
                } else {
                    printf("Child process %d exited abnormally\n", i + 1);
                }
            }
        } else {
            // Fork failed
            fprintf(stderr, "Error spawning child process\n");
        }
    }

    // Stop the timer and calculate elapsed time
    stop_timer();

    // Print statistics
    print_statistics(iterations);

    return 0;
}
