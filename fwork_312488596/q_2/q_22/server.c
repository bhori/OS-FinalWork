#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static volatile sig_atomic_t counterSigint = 0;

// A new signal handler for SIGINT
static void sigint_handler(int sig) {
    counterSigint++;
}

// A new signal handler for SIGUSR1
static void sigusr1_handler(int sig) {
    printf("The number of interrupt signal was sent is: %d\n", counterSigint);
 }

int main(int argc, char **argv) {
    printf("The pid is: %d\n", getpid());

    // Performs registration for the signal handlers
    if(signal(SIGINT, sigint_handler) == SIG_ERR){
        printf("\ncannot catch SIGINT\n");
    }

    if(signal(SIGUSR1, sigusr1_handler) == SIG_ERR){
        printf("\ncannot catch SIGUSR1\n");
    }

    while (1);

    return 0;
}
