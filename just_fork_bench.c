#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spawn.h>
#include <unistd.h>
#include <sys/wait.h>

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

    const char *md5sum_args[] = {
        "md5sum",                   // command
        "file_to_hash.txt",         // file to hash
        NULL                        // end of argument list
    };

    posix_spawn_file_actions_t file_actions;
    posix_spawn_file_actions_init(&file_actions);

    pid_t child_pid;
    int result;

    for (int i = 0; i < iterations; ++i) {
        if ((result = posix_spawn(&child_pid, "/usr/bin/md5sum", &file_actions, NULL, (char *const *)md5sum_args, NULL)) == 0) {
            if (verbose) {
                printf("Spawned md5sum process %d\n", i + 1);
            }

            // Wait for the child process to exit
            int status;
            waitpid(child_pid, &status, 0);

            if (verbose) {
                if (WIFEXITED(status)) {
                    printf("md5sum process %d exited with status %d\n", i + 1, WEXITSTATUS(status));
                } else {
                    printf("md5sum process %d exited abnormally\n", i + 1);
                }
            }
        } else {
            fprintf(stderr, "Error spawning md5sum process: %d\n", result);
        }
    }

    posix_spawn_file_actions_destroy(&file_actions);

    return 0;
}

