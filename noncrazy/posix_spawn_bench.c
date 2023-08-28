#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spawn.h>
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

    const char *child_args[] = {
        "/bin/true",                   // command
        NULL                        // end of argument list
    };

    start_timer();

    pid_t child_pid;
    int result;

    for (int i = 0; i < iterations; ++i) {
        if ((result = posix_spawn(&child_pid, child_args[0], NULL, NULL, (char *const *)child_args, NULL)) == 0) {
            if (verbose) {
                printf("Spawned /bin/true process %d\n", i + 1);
            }

            // Wait for the child process to exit
            int status;
            waitpid(child_pid, &status, 0);

            if (verbose) {
                if (WIFEXITED(status)) {
                    printf("/bin/true process %d exited with status %d\n", i + 1, WEXITSTATUS(status));
                } else {
                    printf("/bin/true process %d exited abnormally\n", i + 1);
                }
            }
        } else {
            fprintf(stderr, "Error spawning /bin/true process: %d\n", result);
        }
    }

    stop_timer();

    print_statistics(iterations);

    return 0;
}

