#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <spawn.h>
#include <unistd.h>

int main() {
    const char *md5sum_args[] = {
        "md5sum",                   // command
        "file_to_hash.txt",         // file to hash
        NULL                        // end of argument list
    };

    posix_spawn_file_actions_t file_actions;
    posix_spawn_file_actions_init(&file_actions);

    pid_t child_pid;
    int result;

    for (int i = 0; i < 1000000; ++i) {
        if ((result = posix_spawn(&child_pid, "/usr/bin/md5sum", &file_actions, NULL, (char *const *)md5sum_args, NULL)) == 0) {
            printf("Spawned md5sum process %d\n", i + 1);
        } else {
            fprintf(stderr, "Error spawning md5sum process: %d\n", result);
        }
    }

    posix_spawn_file_actions_destroy(&file_actions);

    return 0;
}
