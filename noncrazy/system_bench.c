#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "timer.h"

int main(int argc, char *argv[]) {
    int verbose = 0;  // Default to not verbose
    int iterations = 1000000;  // Default number of iterations

    for (int i = 1; i < argc; ++i) {
        if (strcmp(argv[i], "--verbose") == 0) {
            verbose = 1;  // Enable verbose mode if "--verbose" argument is provided
        } else if (strcmp(argv[i], "--iterations") == 0 && i + 1 < argc) {
            iterations = atoi(argv[i + 1]);  // Set custom number of iterations
        }
    }

    start_timer();

    for (int i = 0; i < iterations; ++i) {
        if (verbose) {
            printf("Spawning /bin/true process %d\n", i + 1);
        }

        int status = system("/bin/true");  // Use the 'system' function to execute the command

        if (status == -1) {
            fprintf(stderr, "Error executing /bin/true process\n");
        } else {
            if (WIFEXITED(status)) {
                if (verbose) {
                    printf("/bin/true process %d exited with status %d\n", i + 1, WEXITSTATUS(status));
                }
            } else {
                if (verbose) {
                    printf("/bin/true process %d exited abnormally\n", i + 1);
                }
            }
        }
    }

    stop_timer();

    print_statistics(iterations);

    return 0;
}
