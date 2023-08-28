#define _GNU_SOURCE
#include <unistd.h>
#include <stdio.h>
#include <dlfcn.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef int (*libc_start_main_t)(
    int *(main) (int, char **, char **),
    int argc,
    char **ubp_av,
    void (*init) (void),
    void (*fini) (void),
    void (*rtld_fini) (void),
    void (*stack_end)
);

int __libc_start_main(
    int *(main) (int, char **, char **),
    int argc,
    char **ubp_av,
    void (*init) (void),
    void (*fini) (void),
    void (*rtld_fini) (void),
    void (*stack_end)
) {
    libc_start_main_t original_libc_start_main;
    original_libc_start_main = (libc_start_main_t)dlsym(RTLD_NEXT, "__libc_start_main");

    for(int i = 0; i < 10; ++i) {
        pid_t pid = fork();

        if (pid == 0) {
            // Child process
            return original_libc_start_main(main, argc, ubp_av, init, fini, rtld_fini, stack_end);
        } else if (pid > 0) {
            // Parent process
            waitpid(pid, NULL, 0);
            continue;
        } else {
            // Fork failed
            perror("fork");
            return 1;
        }
    }

    return original_libc_start_main(main, argc, ubp_av, init, fini, rtld_fini, stack_end);
}
