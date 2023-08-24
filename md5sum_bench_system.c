#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

    for (int i = 0; i < iterations; ++i) {
        if (verbose) {
            printf("Spawning md5sum process %d\n", i + 1);
        }

        int status = system("md5sum file_to_hash.txt");  // Use the 'system' function to execute the command

        if (status == -1) {
            fprintf(stderr, "Error executing md5sum process\n");
        } else {
            if (WIFEXITED(status)) {
                if (verbose) {
                    printf("md5sum process %d exited with status %d\n", i + 1, WEXITSTATUS(status));
                }
            } else {
                if (verbose) {
                    printf("md5sum process %d exited abnormally\n", i + 1);
                }
            }
        }
    }

    return 0;
}
