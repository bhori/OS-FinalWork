// Server side!

#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <zconf.h>

static volatile sig_atomic_t counterSigint = 0;

static void
handler(int sig) {
    if (sig == SIGINT) {
        counterSigint++;
        printf("Counter value: %d\n", counterSigint);
    }
    else if (sig == SIGUSR1) {
        printf("The number of interrupt signal was sent is: %d\n", counterSigint);
    }
}

int main(int argc, char **argv) {
    int relevant_pid;
    int status;
    printf("The pid is: %d\n", getpid());

    (void) signal(SIGINT, handler);
    (void) signal(SIGUSR1, handler);

    while (1);

    return 0;
}